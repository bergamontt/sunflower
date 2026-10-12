#pragma once

#include "../monitor.h"
#include "x11window.h"

#include <QSocketNotifier>

namespace sun::monitor
{
    class X11Monitor : public Monitor
    {
    public:
        explicit X11Monitor(QObject* parent = nullptr);

        ~X11Monitor() override;

    private:
        void processX11Events();

        Display* display;
        WindowId rootWindow;
        QSocketNotifier* notifier;
    };
}
