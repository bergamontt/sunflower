#pragma once

#include "window.h"

#include <QString>

namespace sun::monitor::wayland
{
    class KdeWaylandWindowImpl : public WindowImpl
    {
    public:
        KdeWaylandWindowImpl(QString windowId, QString name);
    public:
        QString getName() const override;
        void close() const override;
    public:
        bool operator==(const WindowImpl& other) const override;
    private:
        QString windowId;
        QString name;
    };
} // namespace sun::monitor::wayland
