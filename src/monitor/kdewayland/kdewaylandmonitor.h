#pragma once

#include "monitor.h"

#include <QObject>

namespace sun::monitor::wayland
{
    class KdeWaylandMonitor : public Monitor
    {
    public:
        explicit KdeWaylandMonitor(QObject* parent = nullptr);
        ~KdeWaylandMonitor() override;
    public:
        void startMonitoring() override;
    };
} //sun::monitor::wayland