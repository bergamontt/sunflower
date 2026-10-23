#include "monitorfactory.h"

#ifdef _WIN32
#include "win32/win32monitor.h"
#else
#include "x11/x11monitor.h"
#endif

namespace sun::monitor
{
    std::unique_ptr<Monitor> createMonitor()
    {
#ifdef _WIN32
        return std::make_unique<win32::Win32Monitor>();
#else
        return std::make_unique<x11::X11Monitor>();
#endif
    }
}