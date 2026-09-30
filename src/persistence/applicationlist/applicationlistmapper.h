#pragma once

#include "applicationlist/applicationlist.h"

#include <QSqlQuery>

namespace sun::persistence
{
    struct ApplicationListMapper
    {
        static ApplicationList toApplicationList(const QSqlQuery& query);
    };

    inline ApplicationList ApplicationListMapper::toApplicationList(const QSqlQuery& query)
    {
        return
        {
            query.value("id").toInt(),
            query.value("name").toString()
        };
    }
} // sun::persistence