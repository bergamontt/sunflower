#include "scanning/applicationscannerfactory.h"

#ifdef __linux__ 
#include "scanning/linux/linuxapplicationscanner.h"
#endif

#ifdef _WIN32
#include "scanning/win32/win32applicationscanner.h"
#endif

namespace sun::core
{
    std::unique_ptr<ApplicationScanner> createApplicationScanner()
    {
        #ifdef __linux__
        return std::make_unique<LinuxApplicationScanner>();
        #endif
        #ifdef _WIN32
        return std::make_unique<Win32ApplicationScanner>();
        #endif
    }
} // sun::core