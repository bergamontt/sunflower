#pragma once

#include "monitor.h"
#include "signalgenerator.h"

namespace sun::monitor
{
    class LinuxMonitor : public Monitor<LinuxMonitor> {
    public:
        void startMonitoringImpl();

    private:
        SignalGenerator _signalGenerator;
    };
}
