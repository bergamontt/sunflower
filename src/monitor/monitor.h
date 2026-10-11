#pragma once

#include <QObject>

#include "window.h"

namespace sun::monitor
{
    class Monitor : public QObject
    {
        Q_OBJECT

    public:
        explicit Monitor(QObject* parent = nullptr) : QObject(parent) {}

    signals:
        virtual void usageStarted(sun::monitor::Window window);

        virtual void usageEnded(sun::monitor::Window window);
    };
}
