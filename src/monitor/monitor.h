#pragma once

class Monitor {
public:
    virtual void startMonitoring() = 0;
    virtual ~Monitor() = default;
};