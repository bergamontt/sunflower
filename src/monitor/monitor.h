#pragma once

template <typename Derived>
class Monitor {
public:
    void startMonitoring()
    {
        static_cast<Derived*>(this)->startMonitoringImpl();
    }
};