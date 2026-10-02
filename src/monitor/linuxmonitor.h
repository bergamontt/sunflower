#pragma once

#include "monitor.h"
#include <QHash>
#include <QSocketNotifier>
#include <memory>

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
        void handleEvents();

        void processStarted(pid_t pid);
        void processEnded(pid_t pid);

        int _socket = -1;
        std::unique_ptr<QSocketNotifier> _notifier;
        QHash<pid_t, ProcessInfo> _processes;
    };
}