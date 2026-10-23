#pragma once

#include "schedule/schedule.h"

#include "db/sqlutils.h"

#include <QSqlQuery>
#include <QTime>

namespace sun::persistence
{
    struct ScheduleMapper
    {
        static Schedule toSchedule(const QSqlQuery& query);
        static void bind(QSqlQuery& query, const CreateScheduleDto& dto);
        static void bind(QSqlQuery& query, const UpdateScheduleDto& dto);
    };

    inline Schedule ScheduleMapper::toSchedule(const QSqlQuery& query)
    {
        return
        {
            query.value("id").toInt(),
            query.value("name").toString(),
            toType(query.value("type").toString()),
            query.value("is_active").toBool(),
            query.value("repeat_at").toInt(),
            fromVariant<QTime>(query.value("starts_at")),
            fromVariant<QTime>(query.value("ends_at")),
            fromVariant<int>(query.value("daily_limit"))
        };
    }

    inline void ScheduleMapper::bind(QSqlQuery& query, const CreateScheduleDto& dto)
    {
        query.bindValue(":name", dto.name);
        query.bindValue(":type", toString(dto.type));
        query.bindValue(":is_active", dto.isActive);
        query.bindValue(":repeat_at", dto.repeatAt);
        query.bindValue(":starts_at", toVariant(dto.startsAt));
        query.bindValue(":ends_at", toVariant(dto.endsAt));
        query.bindValue(":daily_limit", toVariant(dto.dailyLimit));
    }

    inline void ScheduleMapper::bind(QSqlQuery& query, const UpdateScheduleDto& dto)
    {
        query.bindValue(":id", dto.id);
        query.bindValue(":name", dto.name);
        query.bindValue(":type", toString(dto.type));
        query.bindValue(":is_active", dto.isActive);
        query.bindValue(":starts_at", toVariant(dto.startsAt));
        query.bindValue(":ends_at", toVariant(dto.endsAt));
        query.bindValue(":daily_limit", toVariant(dto.dailyLimit));
        query.bindValue(":repeat_at", dto.repeatAt);
    }
} // sun::persistence