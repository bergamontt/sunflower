#include "win32monitor.h"
#include "win32window.h"

#include <memory>

using namespace std;

namespace sun::monitor::win32
{
    static unordered_map<HWINEVENTHOOK, Win32Monitor*> monitors;

    void CALLBACK Win32Monitor::winEventProc(
        const HWINEVENTHOOK hook,
        const DWORD event,
        const WindowId windowId,
        const LONG idObject,
        const LONG idChild,
        DWORD,
        DWORD
    )
    {
        if (!windowId || idObject != OBJID_WINDOW || idChild != CHILDID_SELF)
            return;

        const auto it = monitors.find(hook);
        if (it != monitors.end())
            it->second->processWin32Event(event, windowId);
    }

    Win32Monitor::Win32Monitor(QObject* parent) : Monitor(parent)
    {
        createHook = SetWinEventHook(
            EVENT_OBJECT_CREATE,
            EVENT_OBJECT_CREATE,
            nullptr,
            winEventProc,
            0,
            0,
            WINEVENT_OUTOFCONTEXT
        );

        destroyHook = SetWinEventHook(
            EVENT_OBJECT_DESTROY,
            EVENT_OBJECT_DESTROY,
            nullptr,
            winEventProc,
            0,
            0,
            WINEVENT_OUTOFCONTEXT
        );

        if (createHook)
            monitors[createHook] = this;

        if (destroyHook)
            monitors[destroyHook] = this;
    }

    Win32Monitor::~Win32Monitor()
    {
        if (createHook)
        {
            monitors.erase(createHook);
            UnhookWinEvent(createHook);
        }

        if (destroyHook)
        {
            monitors.erase(destroyHook);
            UnhookWinEvent(destroyHook);
        }
    }

    void Win32Monitor::processWin32Event(const DWORD event,WindowId windowId)
    {
        switch (event)
        {
        case EVENT_OBJECT_CREATE:
            usageStarted(Window(make_unique<Win32WindowImpl>(windowId)));
            break;

        case EVENT_OBJECT_DESTROY:
            usageEnded(Window(make_unique<Win32WindowImpl>(windowId)));
            break;

        default:
            break;
        }
    }
}