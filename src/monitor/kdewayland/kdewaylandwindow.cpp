#include "window.h"
#include "kdewaylandwindow.h"

namespace sun::monitor::wayland
{
    KdeWaylandWindow::KdeWaylandWindow(QString windowId, QString name)
    {
    }

    QString KdeWaylandWindow::getName() const
    {
        return QString();
    }

    void KdeWaylandWindow::close() const
    {
    }

    bool KdeWaylandWindow::operator==(const WindowImpl &other) const
    {
        return false;
    }

} // sun::monitor::wayland
