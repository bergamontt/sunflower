#include "linuxmonitor.h"
#include "linuxevent.h"

#include <QDir>

#include <linux/connector.h>
#include <linux/netlink.h>
#include <linux/cn_proc.h>

#include <sys/socket.h>

using namespace std;

namespace sun::monitor
{
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

        switch (event->what)
        {
        case PROC_EVENT_FORK:
            processStarted(event->event_data.fork.child_pid);
            break;

        case PROC_EVENT_EXIT:
            processEnded(event->event_data.exec.process_pid);
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
            const auto pid = static_cast<pid_t>(entry.toLongLong(&ok));
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
