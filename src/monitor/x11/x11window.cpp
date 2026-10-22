#include "x11window.h"

namespace sun::monitor::x11
{
    static QString getNameById(const WindowId windowId)
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

    static QIcon getIconById(const WindowId windowId)
    {
        return {};
    }

    X11WindowImpl::X11WindowImpl(const WindowId windowId)
        : windowId(windowId), name(getNameById(windowId)), icon(getIconById(windowId)) {}

    QString X11WindowImpl::getName() const
    {
        return name;
    }

    QIcon X11WindowImpl::getIcon() const
    {
        return icon;
    }

    void X11WindowImpl::close() const
    {
        Display* display = XOpenDisplay(nullptr);
        if (!display)
            return;

        XDestroyWindow(display, windowId);

        XCloseDisplay(display);
    }

    bool X11WindowImpl::operator==(const WindowImpl& other) const
    {
        const auto* window = dynamic_cast<const X11WindowImpl*>(&other);
        return window && this->windowId == window->windowId;
    }
}
