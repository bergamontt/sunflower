#include "x11window.h"

namespace sun::monitor
{
    QString getNameById(const WindowId windowId)
    {
        Display* display = XOpenDisplay(nullptr);
        if (!display)
            return QString();

        char* name = nullptr;
        XFetchName(display, windowId, &name);
        QString result = name ? QString::fromLocal8Bit(name) : QString{};

        if (name)
            XFree(name);
        XCloseDisplay(display);
        return QString(name);
    }

    X11WindowImpl::X11WindowImpl(const WindowId windowId)
        : _windowId(windowId), _name(getNameById(_windowId)) {}

    QString X11WindowImpl::getName() const
    {
        return _name;
    }

    void X11WindowImpl::minimize() const
    {
        Display* display = XOpenDisplay(nullptr);
        if (!display)
            return;

        XIconifyWindow(display, _windowId, DefaultScreen(display));

        XCloseDisplay(display);
    }
}
