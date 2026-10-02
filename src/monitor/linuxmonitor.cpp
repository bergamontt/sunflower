#include "linuxmonitor.h"

#include <QDir>
#include <QFile>
#include <QSocketNotifier>

#include <linux/connector.h>
#include <linux/netlink.h>
#include <linux/cn_proc.h>

#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>

namespace sun::monitor
{
    LinuxMonitor::~LinuxMonitor()
    {
        if (_notifier)
            _notifier->setEnabled(false);

        if (_socket >= 0)
            ::close(_socket);
    }

    struct ConnectorHeader
    {
        cb_id id;
        __u32 seq;
        __u32 ack;
        __u16 len;
        __u16 flags;
    };

    struct Request
    {
        nlmsghdr header;
        ConnectorHeader message;
        proc_input input;
    };

    void LinuxMonitor::startMonitoring()
    {
        if (_socket >= 0)
            return;
        _socket = ::socket(AF_NETLINK, SOCK_DGRAM, NETLINK_CONNECTOR);
        if (_socket < 0)
            return;

        sockaddr_nl address{};

        address.nl_family = AF_NETLINK;
        address.nl_pid = static_cast<__u32>(::getpid());
        address.nl_groups = CN_IDX_PROC;

        if (::bind(_socket, reinterpret_cast<sockaddr*>(&address), sizeof(address)) < 0)
        {
            ::close(_socket);
            _socket = -1;
            return;
        }

        Request request{};
        request.header.nlmsg_len = NLMSG_LENGTH(sizeof(ConnectorHeader) + sizeof(proc_input));

        request.header.nlmsg_type = NLMSG_DONE;
        request.header.nlmsg_flags = 0;
        request.header.nlmsg_seq = 0;
        request.header.nlmsg_pid = static_cast<__u32>(::getpid());

        request.message.id.idx = CN_IDX_PROC;
        request.message.id.val = CN_VAL_PROC;
        request.message.seq = 0;
        request.message.ack = 0;
        request.message.len = sizeof(proc_input);
        request.message.flags = 0;

        request.input.mcast_op = PROC_CN_MCAST_LISTEN;
        request.input.event_type = static_cast<proc_cn_event>(PROC_EVENT_FORK | PROC_EVENT_EXIT);

        sockaddr_nl kernel{};

        kernel.nl_family = AF_NETLINK;
        kernel.nl_pid = 0;
        kernel.nl_groups = 0;

        const auto sent = ::sendto(
            _socket,
            &request,
            request.header.nlmsg_len,
            0,
            reinterpret_cast<sockaddr*>(&kernel),
            sizeof(kernel));

        if (sent < 0)
        {
            ::close(_socket);
            _socket = -1;
            return;
        }

        const QDir procDirectory(QStringLiteral("/proc"));

        for (const auto& entry : procDirectory.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
        {
            bool ok = false;
            const auto pid = static_cast<pid_t>(entry.toLongLong(&ok));
            if (ok)
                processStarted(pid);
        }

        _notifier = std::make_unique<QSocketNotifier>(_socket, QSocketNotifier::Read);
        connect(
            _notifier.get(),
            &QSocketNotifier::activated,
            this,
            [this]{ handleEvents(); });
    }

    void LinuxMonitor::processStarted(pid_t pid)
    {
        if (_processes.contains(pid))
            return;

        QFile file(QStringLiteral("/proc/%1/comm").arg(pid));

        if (!file.open(QIODevice::ReadOnly))
            return;

        ProcessInfo info;
        info.name = QString::fromUtf8(file.readAll()).trimmed();
        if (info.name.isEmpty())
            return;

        _processes.insert(pid, info);
        emit usageStarted(info);
    }

    void LinuxMonitor::processEnded(pid_t pid)
    {
        const auto it =
            _processes.find(pid);

        if (it == _processes.end())
            return;

        emit usageEnded(it.value());
        _processes.erase(it);
    }

    void LinuxMonitor::handleEvents()
    {
        char buffer[8192];

        while (true)
        {
            const auto size = ::recv(_socket, buffer, sizeof(buffer), MSG_DONTWAIT);

            if (size <= 0)
                return;

            size_t remaining = size;
            auto* data = buffer;
            while (remaining >= sizeof(nlmsghdr))
            {
                nlmsghdr header{};
                std::memcpy(&header, data, sizeof(header));

                if (header.nlmsg_len < sizeof(nlmsghdr) || header.nlmsg_len > remaining)
                    break;

                const auto payloadSize = header.nlmsg_len - sizeof(nlmsghdr);

                if (payloadSize < sizeof(ConnectorHeader))
                    break;

                ConnectorHeader message{};
                std::memcpy(&message, data + sizeof(nlmsghdr), sizeof(message));

                if (message.id.idx == CN_IDX_PROC &&
                    message.id.val == CN_VAL_PROC &&
                    message.len >= sizeof(proc_event) &&
                    sizeof(ConnectorHeader) +
                        message.len <= payloadSize)
                {
                    proc_event event{};
                    std::memcpy(
                        &event,
                        data + sizeof(nlmsghdr) + sizeof(ConnectorHeader),
                        sizeof(event));

                    switch (event.what)
                    {
                    case PROC_EVENT_FORK:
                    {
                        const auto& fork = event.event_data.fork;
                        if (fork.child_pid == fork.child_tgid)
                            processStarted(fork.child_tgid);
                        break;
                    }
                    case PROC_EVENT_EXIT:
                    {
                        const auto& exit = event.event_data.exit;
                        if (exit.process_pid == exit.process_tgid)
                            processEnded(exit.process_tgid);
                        break;
                    }
                    default:
                        break;
                    }
                }

                const auto messageSize = NLMSG_ALIGN(header.nlmsg_len);

                if (messageSize > remaining)
                    break;

                data += messageSize;
                remaining -= messageSize;
            }
        }
    }
}