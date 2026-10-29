#include "x11monitor.h"

#include <X11/Xatom.h>

using namespace std;

namespace sun::monitor::x11
{
    X11Monitor::X11Monitor(QObject* parent)
        : Monitor(parent), display(nullptr), rootWindow(0), notifier(nullptr) {}

    void X11Monitor::startMonitoring()
    {
        display = XOpenDisplay(nullptr);
        if (!display)
            return;

        rootWindow = DefaultRootWindow(display);
        XSelectInput(display, rootWindow, SubstructureNotifyMask);
        XFlush(display);

        WindowId rootReturn;
        WindowId parentReturn;
        WindowId* children = nullptr;
        unsigned int childCount = 0;

        if (XQueryTree(
                display,
                rootWindow,
                &rootReturn,
                &parentReturn,
                &children,
                &childCount))
        {
            for (unsigned int i = 0; i < childCount; ++i)
            {
                X11WindowImpl windowImpl(children[i]);
                if (!windowImpl.getName().isEmpty())
                    usageStarted(Window(make_shared<X11WindowImpl>(children[i])));
            }
        }

        if (children)
            XFree(children);

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
                auto window = make_shared<X11WindowImpl>(windowId);
                if (!window->getName().isEmpty())
                    usageStarted(Window(window));
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
