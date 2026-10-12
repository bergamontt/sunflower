#include "x11window.h"

namespace sun::monitor
{
    QString getNameById(const WindowId windowId)
    {
        Display* display = XOpenDisplay(nullptr);
        if (!display)
            return {};

        char* name = nullptr;
        XFetchName(display, windowId, &name);
        QString result = name ? QString::fromLocal8Bit(name) : QString{};

        if (name)
            XFree(name);
        XCloseDisplay(display);
        return result;
    }

    X11WindowImpl::X11WindowImpl(const WindowId windowId)
        : windowId(windowId), name(getNameById(windowId)) {}

    QString X11WindowImpl::getName() const
    {
        return name;
    }

    void X11WindowImpl::minimize() const
    {
        Display* display = XOpenDisplay(nullptr);
        if (!display)
            return;

        XIconifyWindow(display, windowId, DefaultScreen(display));

        XCloseDisplay(display);
    }
}
