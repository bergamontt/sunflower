#pragma once

#include <QObject>

#include "window.h"

class Monitor : public QObject
{
    Q_OBJECT

public:
    explicit Monitor(QObject* parent = nullptr) : QObject(parent) {}

signals:
    virtual void usageStarted(Window window);

    virtual void usageEnded(Window window);
};