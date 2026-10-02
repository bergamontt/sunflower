#pragma once

#include "monitor.h"

namespace sun::monitor
{
    class LinuxMonitor : public Monitor
    {
        Q_OBJECT

    public:
        explicit LinuxMonitor(QObject* parent = nullptr) : Monitor(parent) {}

        ~LinuxMonitor() override = default;

        void startMonitoring() override;
    };
}