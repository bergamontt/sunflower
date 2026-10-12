#pragma once

#include <X11/Xlib.h>

#include "../window.h"

namespace sun::monitor
{
    using WindowId = ::Window;

    class X11WindowImpl : public WindowImpl
    {
    public:
        explicit X11WindowImpl(WindowId windowId);

        [[nodiscard]] QString getName() const override;

        void minimize() const override;

    private:
        WindowId windowId;

        QString name;
    };
}
