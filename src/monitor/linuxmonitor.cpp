#include "linuxmonitor.h"

#include <QDir>
#include <QFile>

#include <linux/connector.h>
#include <linux/netlink.h>
#include <linux/cn_proc.h>

#include <sys/socket.h>
#include <unistd.h>

#include <fstream>

using namespace std;

namespace sun::monitor
{
    QString getProcessName(const pid_t pid)
    {
        ifstream file("/proc/" + to_string(pid) + "/comm");
        if (!file.is_open())
            return "";
        string name;
        getline(file, name);
        return name.data();
    }

    void createSocket(int& sock)
    {
        if (sock >= 0)
            return;
        sock = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_CONNECTOR);
    }

    void closeSocket(int& socket)
    {
        if (socket < 0)
            return;
        ::close(socket);
        socket = -1;
    }

    class ProcessNetlinkAddress
    {
    public:
        ProcessNetlinkAddress()
        {
            addr.nl_family = AF_NETLINK;
            addr.nl_pid = getpid();
            addr.nl_groups = CN_IDX_PROC;
        }

        bool bindTo(const int sock) const
        {
            return bind(sock, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr)) >= 0;
        }

    private:
        sockaddr_nl addr{};
    };

    class ProcessEventSubscription
    {
    public:
        ProcessEventSubscription()
            : buffer_(NLMSG_SPACE(sizeof(cn_msg) + sizeof(proc_cn_mcast_op)))
        {
            auto* header = reinterpret_cast<nlmsghdr*>(buffer_.data());
            header->nlmsg_len = NLMSG_LENGTH(sizeof(cn_msg) + sizeof(proc_cn_mcast_op));
            header->nlmsg_type = NLMSG_DONE;
            header->nlmsg_flags = 0;
            header->nlmsg_pid = getpid();

            auto* cn = static_cast<cn_msg*>(NLMSG_DATA(header));
            cn->id.idx = CN_IDX_PROC;
            cn->id.val = CN_VAL_PROC;
            cn->len = sizeof(proc_cn_mcast_op);
            cn->flags = 0;

            auto* operation = reinterpret_cast<proc_cn_mcast_op*>(cn->data);
            *operation = PROC_CN_MCAST_LISTEN;
        }

        bool subscribe(const int sock) const
        {
            auto* header = reinterpret_cast<const nlmsghdr*>(buffer_.data());
            iovec iov{
                const_cast<nlmsghdr*>(header),
                header->nlmsg_len
            };

            msghdr message{};
            message.msg_iov = &iov;
            message.msg_iovlen = 1;

            return sendmsg(sock, &message, 0) >= 0;
        }

    private:
        std::vector<std::byte> buffer_;
    };

    bool subscribeToEvents(const int sock)
    {
        ProcessNetlinkAddress address;
        if (!address.bindTo(sock))
        {
            return false;
        }

        ProcessEventSubscription subscription;
        if (!subscription.subscribe(sock))
        {
            return false;
        }

        return true;
    }

    LinuxMonitor::~LinuxMonitor()
    {
        closeSocket(_socket);
    }

    void LinuxMonitor::startMonitoring()
    {
        createSocket(_socket);
        if (_socket < 0)
            return;

        bool subscribed = subscribeToEvents(_socket);
        if (!subscribed)
        {
            closeSocket(_socket);
            return;
        }

        scanRunningProcesses();

        char buffer[4096];
        while (true)
        {
            const ssize_t n = recv(_socket, buffer, sizeof(buffer), 0);
            if (n <= 0)
                break;
            handleMessages(buffer, n);
        }
    }

    void LinuxMonitor::handleMessages(char* buffer, const ssize_t size)
    {
        auto header = reinterpret_cast<nlmsghdr*>(buffer);
        ssize_t remaining = size;
        while (NLMSG_OK(header, remaining))
        {
            handleMessage(header);
            header = NLMSG_NEXT(header, remaining);
        }
    }

    void LinuxMonitor::handleMessage(nlmsghdr* header)
    {
        auto* cn = static_cast<cn_msg*>(NLMSG_DATA(header));
        auto* event = reinterpret_cast<proc_event*>(cn->data);
        handleEvent(*event);
    }

    void LinuxMonitor::handleEvent(const proc_event& event)
    {
        switch (event.what)
        {
        case PROC_EVENT_FORK:
            processStarted(event.event_data.fork.child_pid);
            break;

        case PROC_EVENT_EXIT:
            processEnded(event.event_data.exec.process_pid);
            break;

        default:
            break;
        }
    }

    void LinuxMonitor::scanRunningProcesses()
    {
        const QDir procDir("/proc");
        const QStringList entries = procDir.entryList(
            QDir::Dirs | QDir::NoDotAndDotDot,
            QDir::Name
        );

        for (const QString& entry : entries)
        {
            bool ok = false;
            const pid_t pid = static_cast<pid_t>(entry.toLongLong(&ok));
            if (!ok || pid <= 0)
                continue;
            processStarted(pid);
        }
    }

    void LinuxMonitor::processStarted(const pid_t pid)
    {
        if (_processes.contains(pid))
            return;
        const QString name = getProcessName(pid);
        const ProcessInfo proc(pid, name);
        _processes.insert(pid, proc);
        emit usageStarted(proc);
    }

    void LinuxMonitor::processEnded(const pid_t pid)
    {
        if (!_processes.contains(pid))
            return;
        const ProcessInfo proc = _processes.value(pid);
        _processes.remove(pid);
        emit usageEnded(proc);
    }
}
