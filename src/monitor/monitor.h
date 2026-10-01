#pragma once
#include <concepts>

namespace sun::monitor
{
    template <typename T>
    concept MonitorImplementation = requires(T& obj)
    {
        { obj.startMonitoringImpl() } -> std::same_as<void>;
    };

    template <MonitorImplementation Derived>
    class Monitor
    {
    public:
        void startMonitoring()
        {
            static_cast<Derived*>(this)->startMonitoringImpl();
        }
    };
}