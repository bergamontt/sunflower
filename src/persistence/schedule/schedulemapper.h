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
            toLockType(query.value("lock_type").toString()),
            query.value("repeat_at").toInt(),
            fromVariant<QTime>(query.value("starts_at")),
            fromVariant<QTime>(query.value("ends_at")),
            fromVariant<int>(query.value("daily_limit")),
            fromVariant<QString>(query.value("lock_hash")),
            fromVariant<int>(query.value("unlock_after")),
            fromVariant<QDateTime>(query.value("unlock_requested_at"))
        };
    }

    inline void ScheduleMapper::bind(QSqlQuery& query, const CreateScheduleDto& dto)
    {
        query.bindValue(":name", dto.name);
        query.bindValue(":type", toString(dto.type));
        query.bindValue(":lock_type", toString(dto.lockType));
        query.bindValue(":repeat_at", dto.repeatAt);
        query.bindValue(":starts_at", toVariant(dto.startsAt));
        query.bindValue(":ends_at", toVariant(dto.endsAt));
        query.bindValue(":daily_limit", toVariant(dto.dailyLimit));
        query.bindValue(":lock_hash", toVariant(dto.lockHash));
        query.bindValue(":unlock_after", toVariant(dto.unlockAfter));
        query.bindValue(":unlock_requested_at", toVariant(dto.unlockRequestedAt));
    }

    inline void ScheduleMapper::bind(QSqlQuery& query, const UpdateScheduleDto& dto)
    {
        query.bindValue(":id", dto.id);
        query.bindValue(":name", dto.name);
        query.bindValue(":type", toString(dto.type));
        query.bindValue(":starts_at", toVariant(dto.startsAt));
        query.bindValue(":ends_at", toVariant(dto.endsAt));
        query.bindValue(":daily_limit", toVariant(dto.dailyLimit));
        query.bindValue(":repeat_at", dto.repeatAt);
        query.bindValue(":lock_type", toString(dto.lockType));
        query.bindValue(":lock_hash", toVariant(dto.lockHash));
        query.bindValue(":unlock_after", toVariant(dto.unlockAfter));
        query.bindValue(":unlock_requested_at", toVariant(dto.unlockRequestedAt));
    }
} // sun::persistence