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
        QString icon;
        QString source;
    };

    struct CreateApplicationDto
    {
        QString name;
        QString processName;
        QString icon;
        QString source;
    };

    struct UpdateApplicationDto
    {
        int id;
        QString name;
        QString processName;
        QString icon;
        QString source;
    };

    inline bool operator==(const Application& a, const Application& b)
    {
        return a.id == b.id && a.name == b.name
            && a.processName == b.processName && a.icon == b.icon
            && a.source == b.source;
    }
} // sun::persistence