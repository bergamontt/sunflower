#pragma once

#include "../monitor.h"

namespace sun::monitor::fallback
{
    class FallbackMonitor : public Monitor
    {
    public:
        explicit FallbackMonitor(QObject *parent = nullptr) {}

        void startMonitoring() override {}

        ~FallbackMonitor() override {}
    };
}
