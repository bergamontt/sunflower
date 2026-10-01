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
} // sun::persistence