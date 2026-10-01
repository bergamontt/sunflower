#pragma once

namespace sun::monitor
{
    class Monitor
    {
    public:
        virtual ~Monitor() = default;

        virtual void startMonitoring() = 0;
    };
}