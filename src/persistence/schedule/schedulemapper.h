#pragma once

#include "schedule/schedule.h"

#include <QSqlQuery>

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

    inline void ScheduleMapper::bind(QSqlQuery& query, const CreateScheduleDto& dto)
    {
        query.bindValue(":name", dto.name);
        query.bindValue(":type", toString(dto.type));
        query.bindValue(":starts_at", dto.startsAt);
        query.bindValue(":ends_at", dto.endsAt);
        query.bindValue(":daily_limit", dto.dailyLimit);
        query.bindValue(":repeat_at", dto.repeatAt);
        query.bindValue(":lock_type", toString(dto.lockType));
        query.bindValue(":lock_hash", dto.lockHash);
        query.bindValue(":unlock_after", dto.unclockAfter);
        query.bindValue(":unlock_requested_at", dto.unlockRequestedAt.value_or(std::nullopt));
    }

    inline void ScheduleMapper::bind(QSqlQuery& query, const UpdateScheduleDto& dto)
    {
        query.bindValue(":id", dto.id);
        query.bindValue(":name", dto.name);
        query.bindValue(":type", toString(dto.type));
        query.bindValue(":starts_at", dto.startsAt);
        query.bindValue(":ends_at", dto.endsAt);
        query.bindValue(":daily_limit", dto.dailyLimit);
        query.bindValue(":repeat_at", dto.repeatAt);
        query.bindValue(":lock_type", toString(dto.lockType));
        query.bindValue(":lock_hash", dto.lockHash);
        query.bindValue(":unlock_after", dto.unclockAfter);
        query.bindValue(":unlock_requested_at", dto.unlockRequestedAt.value_or(std::nullopt));
    }
} // sun::persistence