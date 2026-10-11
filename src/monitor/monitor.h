#pragma once

#include <QObject>

#ifdef CursorShape
#undef CursorShape
#endif

#include "window.h"

namespace sun::monitor
{
    class Monitor : public QObject
    {
        Q_OBJECT

    public:
        explicit Monitor(QObject* parent = nullptr) : QObject(parent) {}

    signals:
        virtual void usageStarted(Window window);

        virtual void usageEnded(Window window);
    };
}
