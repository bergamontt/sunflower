#include "monitorfactory.h"

#ifdef _WIN32
#include "win32/win32monitor.h"
#elif defined(SUN_USE_X11)
#include "x11/x11monitor.h"
#else
#include "fallback/fallbackmonitor.h"
#endif

namespace sun::monitor
{
    std::unique_ptr<Monitor> createMonitor()
    {
#ifdef _WIN32
        return std::make_unique<win32::Win32Monitor>();
#elif defined(SUN_USE_X11)
        return std::make_unique<x11::X11Monitor>();
#else
        return std::make_unique<fallback::FallbackMonitor>();
#endif
    }
}