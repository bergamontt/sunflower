#include <QDebug>

#include "x11monitor.h"

using namespace std;

namespace sun::monitor::x11
{
    X11Monitor::X11Monitor(QObject* parent)
        : Monitor(parent), display(nullptr), rootWindow(0), notifier(nullptr)
    {
        display = XOpenDisplay(nullptr);
        if (!display)
            return;

        rootWindow = DefaultRootWindow(display);
        XSelectInput(display, rootWindow, SubstructureNotifyMask);
        XFlush(display);

        notifier = new QSocketNotifier(
            ConnectionNumber(display),
            QSocketNotifier::Read,
            this
        );
        connect(
            notifier,
            &QSocketNotifier::activated,
            this, [this](auto...) { processX11Events(); }
        );
    }

    X11Monitor::~X11Monitor()
    {
        if (notifier)
        {
            notifier->setEnabled(false);
            delete notifier;
            notifier = nullptr;
        }
        if (display)
        {
            XCloseDisplay(display);
            display = nullptr;
        }
    }

    void X11Monitor::processX11Events()
    {
        if (!display)
            return;

        while (XPending(display) > 0)
        {
            XEvent event;
            XNextEvent(display, &event);

            switch (event.type)
            {
            case CreateNotify:
                {
                    WindowId windowId = event.xcreatewindow.window;
                    usageStarted(Window(make_shared<X11WindowImpl>(windowId)));
                    break;
                }

            case DestroyNotify:
                {
                    WindowId windowId = event.xdestroywindow.window;
                    usageEnded(Window(make_shared<X11WindowImpl>(windowId)));
                    break;
                }

            default:
                    break;
            }
        }
    }
}
