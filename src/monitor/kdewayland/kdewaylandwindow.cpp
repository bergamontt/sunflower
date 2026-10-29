#include "window.h"
#include "kdewayland/kdewaylandwindow.h"
#include "kdewayland/kwinscriptutils.h"

namespace sun::monitor::wayland
{
    namespace
    {
        const inline auto blocker_path = ":/kdewayland/scripts/blocker.js";
        const inline auto blocker_prefix = "blocker_";
    }

    KdeWaylandWindowImpl::KdeWaylandWindowImpl(QString windowId, QString name)
        : windowId(std::move(windowId))
        , name(std::move(name))
    {}

    QString KdeWaylandWindowImpl::getName() const
    {
        return name;
    }

    void KdeWaylandWindowImpl::close() const
    {
        utils::executeScript(blocker_path, blocker_prefix + windowId, {windowId});
    }

    bool KdeWaylandWindowImpl::operator==(const WindowImpl &other) const
    {
        const auto* window = dynamic_cast<const KdeWaylandWindowImpl*>(&other);
        return window && this->windowId == window->windowId;
    }
} // sun::monitor::wayland
