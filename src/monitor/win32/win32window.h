#pragma once

#include <windows.h>

#include "../window.h"

namespace sun::monitor::win32
{
    using WindowId = ::HWND;

    class Win32WindowImpl : public WindowImpl
    {
    public:
        explicit Win32WindowImpl(WindowId windowId);

        [[nodiscard]] QString getName() const override;

        void close() const override;

        [[nodiscard]] bool operator==(const WindowImpl& other) const override;

    private:
        WindowId windowId;

        QString name;
    };
}
