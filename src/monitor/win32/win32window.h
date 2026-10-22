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

        [[nodiscard]] QIcon getIcon() const override;

        void close() const override;

    private:
        WindowId windowId;

        QString name;

        QIcon icon;
    };
}
