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

    struct CreateApplicationDto
    {
        QString name;
        QString processName;
    };

    struct UpdateApplicationDto
    {
        int id;
        QString name;
        QString processName;
    };

    inline bool operator==(const Application& a, const Application& b)
    {
        return a.id == b.id && a.name == b.name && a.processName == b.processName;
    }
} // sun::persistence