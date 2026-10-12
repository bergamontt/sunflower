#include "win32window.h"

using namespace std;

namespace sun::monitor::win32
{
    QString getNameById(const WindowId windowId)
    {
        if (windowId == nullptr)
            return {};

        const int length = GetWindowTextLengthW(windowId);
        vector<wchar_t> buffer(length + 1);
        const int copied = GetWindowTextW(
            windowId,
            buffer.data(),
            buffer.size()
        );

        if (copied == 0)
            return {};
        return QString::fromWCharArray(buffer.data(), copied);
    }


    Win32WindowImpl::Win32WindowImpl(const WindowId windowId)
        : windowId(windowId), name(getNameById(windowId)) {}

    QString Win32WindowImpl::getName() const
    {
        return name;
    }

    void Win32WindowImpl::close() const
    {
        if (windowId != nullptr)
            PostMessageW(windowId, WM_CLOSE, 0, 0);
    }
}
