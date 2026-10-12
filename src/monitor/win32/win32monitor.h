#pragma once

#include <windows.h>

#include "../monitor.h"
#include "win32window.h"

namespace sun::monitor::win32
{
    class Win32Monitor : public Monitor
    {
    public:
        explicit Win32Monitor(QObject *parent = nullptr);

        ~Win32Monitor() override;

    private:
        void processWin32Event(DWORD event, WindowId windowId);

        static void CALLBACK winEventProc(
            HWINEVENTHOOK hook,
            DWORD event,
            WindowId windowId,
            LONG idObject,
            LONG idChild,
            DWORD,
            DWORD
        );

        HWINEVENTHOOK createHook;
        HWINEVENTHOOK destroyHook;
    };
}
