#include "win32monitor.h"
#include "win32window.h"

#include <memory>
#include <unordered_map>
#include <QDebug>

using namespace std;

namespace sun::monitor::win32
{
    static unordered_map<HWINEVENTHOOK, Win32Monitor*> monitors;

    static BOOL CALLBACK enumWindowsProc(WindowId id, LPARAM lParam)
    {
        auto* monitor = reinterpret_cast<Win32Monitor*>(lParam);

        if (!IsWindowVisible(id))
            return TRUE;

        const auto window = make_shared<Win32WindowImpl>(id);
        if (!window->getName().isEmpty())
            monitor->usageStarted(Window(window));
        return TRUE;
    }

    void CALLBACK Win32Monitor::winEventProc(
        HWINEVENTHOOK hook,
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

    Win32Monitor::Win32Monitor(QObject* parent)
        : Monitor(parent),
          createHook(nullptr),
          destroyHook(nullptr)
    {}

    void Win32Monitor::startMonitoring()
    {
        createHook = SetWinEventHook(
            EVENT_OBJECT_CREATE,
            EVENT_OBJECT_CREATE,
            nullptr,
            winEventProc,
            0,
            0,
            WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS
        );

        destroyHook = SetWinEventHook(
            EVENT_OBJECT_DESTROY,
            EVENT_OBJECT_DESTROY,
            nullptr,
            winEventProc,
            0,
            0,
            WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS
        );

        if (createHook)
            monitors[createHook] = this;

        if (destroyHook)
            monitors[destroyHook] = this;

        EnumWindows(enumWindowsProc, reinterpret_cast<LPARAM>(this));
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

    void Win32Monitor::processWin32Event(const DWORD event, WindowId windowId)
    {
        switch (event)
        {
        case EVENT_OBJECT_CREATE:
        {
            auto window = make_shared<Win32WindowImpl>(windowId);
            if (!window->getName().isEmpty())
                usageStarted(Window(window));
            break;
        }

        case EVENT_OBJECT_DESTROY:
            usageEnded(Window(make_shared<Win32WindowImpl>(windowId)));
            break;

        default:
            break;
        }
    }
}