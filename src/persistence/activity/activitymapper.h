#pragma once

#include "activity/activity.h"

#include <QSqlQuery>

namespace sun::persistence
{
    struct ActivityMapper
    {
        static Activity toActivity(const QSqlQuery& query);
    };

    inline Activity ActivityMapper::toActivity(const QSqlQuery& query)
    {
        return
        {
            query.value("id").toInt(),
            query.value("application_id").toInt(),
            query.value("started_at").toDateTime(),
            query.value("ended_at").toDateTime()
        };
    }
} // sun::persistence