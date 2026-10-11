#include "x11monitor.h"

using namespace std;

namespace sun::monitor
{
    X11Monitor::X11Monitor(QObject* parent)
        : Monitor(parent), _display(nullptr), _rootWindow(0), _notifier(nullptr)
    {
        _display = XOpenDisplay(nullptr);
        if (!_display)
            return;

        _rootWindow = DefaultRootWindow(_display);
        XSelectInput(_display, _rootWindow, SubstructureNotifyMask);
        XFlush(_display);

        _notifier = new QSocketNotifier(
            ConnectionNumber(_display),
            QSocketNotifier::Read,
            this
        );
        connect(
            _notifier,
            &QSocketNotifier::activated,
            this, [this](auto...) { processX11Events(); }
        );
    }

    X11Monitor::~X11Monitor()
    {
        if (_notifier)
        {
            _notifier->setEnabled(false);
            delete _notifier;
            _notifier = nullptr;
        }
        if (_display)
        {
            XCloseDisplay(_display);
            _display = nullptr;
        }
    }

    void X11Monitor::processX11Events()
    {
        if (!_display)
            return;

        while (XPending(_display) > 0)
        {
            XEvent event;
            XNextEvent(_display, &event);

            switch (event.type)
            {
            case CreateNotify:
                {
                    WindowId windowId = event.xcreatewindow.window;
                    usageStarted(Window(make_unique<X11WindowImpl>(windowId)));
                    break;
                }

            case DestroyNotify:
                {
                    WindowId windowId = event.xdestroywindow.window;
                    usageEnded(Window(make_unique<X11WindowImpl>(windowId)));
                    break;
                }

            default: ;
            }
        }
    }
}
