#include "monitorfactory.h"

#ifdef _WIN32
#include "win32/win32monitor.h"
#else

#include <QByteArray>
#include <QGuiApplication>
#include <QString>

#if defined(SUN_USE_X11)
#include "x11/x11monitor.h"
#endif

#if defined(SUN_USE_KDE_WAYLAND)
#include "kdewayland/kdewaylandmonitor.h"
#endif

#include "fallback/fallbackmonitor.h"
#endif

namespace sun::monitor
{

#ifndef _WIN32
    static bool isKdeWayland()
    {
        QString platform = QGuiApplication::platformName();
        bool isWayland = (platform == "wayland") || (qgetenv("XDG_SESSION_TYPE").toLower() == "wayland");
        bool isKde = qgetenv("XDG_CURRENT_DESKTOP").toUpper().split(':').contains("KDE");
        return isWayland && isKde;
    }
#endif

    std::unique_ptr<Monitor> createMonitor()
    {
#ifdef _WIN32
        return std::make_unique<win32::Win32Monitor>();
#else
#if defined(SUN_USE_KDE_WAYLAND)
        if (isKdeWayland())
        {
            return std::make_unique<wayland::KdeWaylandMonitor>();
        }
#endif

#if defined(SUN_USE_X11)
        return std::make_unique<x11::X11Monitor>();
#else
        return std::make_unique<fallback::FallbackMonitor>();
#endif
#endif
    }
}