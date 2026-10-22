#include "win32window.h"

using namespace std;

namespace sun::monitor::win32
{
    static QString getNameById(const WindowId windowId)
    {
        if (windowId == nullptr)
            return {};

        const int length = GetWindowTextLengthW(windowId);
        vector<wchar_t> buffer(length + 1);
        const int copied = GetWindowTextW(
            windowId,
            buffer.data(),
            static_cast<int>(buffer.size())
        );

        if (copied == 0)
            return {};
        return QString::fromWCharArray(buffer.data(), copied);
    }

    static QIcon getIconById(const WindowId windowId)
    {
        return {};
    }

    Win32WindowImpl::Win32WindowImpl(const WindowId windowId)
        : windowId(windowId), name(getNameById(windowId)), icon(getIconById(windowId)) {}

    QString Win32WindowImpl::getName() const
    {
        return name;
    }

    QIcon Win32WindowImpl::getIcon() const
    {
        return icon;
    }

    void Win32WindowImpl::close() const
    {
        if (windowId != nullptr)
            PostMessageW(windowId, WM_CLOSE, 0, 0);
    }

    bool Win32WindowImpl::operator==(const WindowImpl& other) const
    {
        const auto* window = dynamic_cast<const Win32WindowImpl*>(&other);
        return window && this->windowId == window->windowId;
    }
}
