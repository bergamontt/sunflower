#pragma once

#include "schedule/schedule.h"

#include <QSqlQuery>

namespace sun::persistence
{
    struct ScheduleMapper
    {
        static Schedule toSchedule(const QSqlQuery& query);
    };

    inline Schedule ScheduleMapper::toSchedule(const QSqlQuery& query)
    {
        return
        {
            query.value("id").toInt(),
            query.value("name").toString(),
            toType(query.value("type").toString()),
            query.value("starts_at").toTime(),
            query.value("ends_at").toTime(),
            query.value("daily_limit").toInt(),
            query.value("repeat_at").toInt(),
            toLockType(query.value("lock_type").toString()),
            query.value("lock_hash").toString(),
            query.value("unlock_after").toInt(),
            query.value("unclock_requested_at").toDateTime()
        };
    }

} // sun::persistence