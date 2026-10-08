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
    }

    void LinuxMonitor::processStarted(pid_t pid)
    {
    }

    void LinuxMonitor::processEnded(pid_t pid)
    {
    }

    void LinuxMonitor::handleEvents()
    {
    }
}