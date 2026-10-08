#include "linuxmonitor.h"

#include <QDir>
#include <QFile>
#include <QSocketNotifier>

#include <linux/connector.h>
#include <linux/netlink.h>
#include <linux/cn_proc.h>

#include <sys/socket.h>
#include <unistd.h>

#include <fstream>

using namespace std;

namespace sun::monitor
{
    QString getProcessName(const pid_t pid) {
        ifstream file("/proc/" + to_string(pid) + "/comm");
        if (!file.is_open())
            return "";
        string name;
        getline(file, name);
        return name.data();
    }


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

    void LinuxMonitor::handleEvents()
    {
    }
}