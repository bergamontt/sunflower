#pragma once

#include "../window.h"

#include <X11/Xlib.h>

namespace sun::monitor::x11
{
    using WindowId = ::Window;

    class X11WindowImpl : public WindowImpl
    {
    public:
        explicit X11WindowImpl(WindowId windowId);

        [[nodiscard]] QString getName() const override;

        [[nodiscard]] QIcon getIcon() const override;

        void close() const override;

        [[nodiscard]] bool operator==(const WindowImpl& other) const override;

    private:
        WindowId windowId;

        QString name;

        QIcon icon;
    };
}
