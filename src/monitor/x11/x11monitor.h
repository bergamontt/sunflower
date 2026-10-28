#pragma once

#include "../monitor.h"
#include "x11window.h"

#include <QSocketNotifier>

namespace sun::monitor::x11
{
    class X11Monitor : public Monitor
    {
    public:
        explicit X11Monitor(QObject* parent = nullptr);

        void startMonitoring() override;

        ~X11Monitor() override;

    private:
        void processX11Events();

        Display* display;
        WindowId rootWindow;
        QSocketNotifier* notifier;
    };
}
