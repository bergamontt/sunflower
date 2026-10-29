#include "kdewayland/kdewaylandmonitor.h"
#include "kdewayland/kdewaylandwindow.h"
#include "kdewayland/kwinscriptutils.h"

#include <QtDBus/QDBusConnection>

namespace sun::monitor::wayland
{
    namespace
    {
        const inline auto DBUS_SERVICE = "org.sun.monitor.Receiver";
        const inline auto DBUS_PATH = "/Receiver";
        const inline auto DBUS_INTERFACE = "org.sun.monitor.KWinReceiver";
        const inline auto SCRIPT_PATH = ":/kdewayland/scripts/monitor.js";
        const inline auto PLUGIN_NAME = "sun_kde_wayland_monitor";
    }

    KdeWaylandMonitor::KdeWaylandMonitor(QObject *parent)
        : Monitor(parent)
    {}

    KdeWaylandMonitor::~KdeWaylandMonitor()
    {
        if (scriptId >= 0)
        {
            utils::stopScript(scriptId);
            utils::unloadScript(PLUGIN_NAME);
        }
    }

    void KdeWaylandMonitor::startMonitoring()
    {
        auto bus = QDBusConnection::sessionBus();
        bus.registerService(DBUS_SERVICE);
        bus.registerObject(DBUS_PATH, this, QDBusConnection::ExportAllSlots);
        
        script = utils::createScript(
            SCRIPT_PATH,
            {DBUS_SERVICE, DBUS_PATH, DBUS_INTERFACE}
        );

        if (!script)
        {
            return;
        }

        scriptId = utils::loadScript(script->fileName(), PLUGIN_NAME);
        if (scriptId >= 0)
        {
            utils::runScript(scriptId);
        }
    }

    void KdeWaylandMonitor::onWindowOpened(const QString& windowId, const QString& name)
    {
        auto impl = std::make_shared<KdeWaylandWindowImpl>(windowId, name);
        emit usageStarted(Window(std::move(impl)));
    }

    void KdeWaylandMonitor::onWindowClosed(const QString& windowId, const QString& name)
    {
        auto impl = std::make_shared<KdeWaylandWindowImpl>(windowId, name);
        emit usageEnded(Window(std::move(impl)));
    }
} // sun::monitor::wayland