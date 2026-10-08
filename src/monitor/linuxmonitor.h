#pragma once

#include "monitor.h"
#include <QHash>
#include <QSocketNotifier>
#include <linux/netlink.h>
#include <linux/cn_proc.h>

namespace sun::monitor
{
    class LinuxMonitor : public Monitor
    {
        Q_OBJECT

    public:
        explicit LinuxMonitor(QObject* parent = nullptr) : Monitor(parent) {}

        ~LinuxMonitor() override;

        void startMonitoring() override;

    private:
        void handleMessages(char* buffer, ssize_t size);
        void handleMessage(nlmsghdr* header);
        void handleEvent(const proc_event& event);

        void scanRunningProcesses();

        void processStarted(pid_t pid);
        void processEnded(pid_t pid);

        int _socket = -1;
        QHash<pid_t, ProcessInfo> _processes;
    };
}