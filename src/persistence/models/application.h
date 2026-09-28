#pragma once
#include <QString>
#include <QList>

namespace sun::persistence
{
    struct Application
    {
        int id;
        QString name;
        QString processName;
    };
} // sun::persistence