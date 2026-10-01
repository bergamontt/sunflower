#pragma once

#include "monitor.h"
#include "signalgenerator.h"

namespace sun::monitor
{
    class LinuxMonitor : public Monitor
    {
    public:
        void startMonitoring() override;

    private:
        SignalGenerator _signalGenerator;
    };
}
