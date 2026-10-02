#pragma once

#include "activity/activity.h"

#include <QSqlQuery>

namespace sun::persistence
{
    struct ActivityMapper
    {
        static Activity toActivity(const QSqlQuery& query);
        static void bind(QSqlQuery& query, const CreateActivityDto& dto);
        static void bind(QSqlQuery& query, const UpdateActivityDto& dto);
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

    inline void bind(QSqlQuery& query, const CreateActivityDto& dto) 
    {
        query.bindValue(":application_id", dto.applicationId);
        query.bindValue(":started_at", dto.startedAt);
        query.bindValue(":ended_at", dto.endedAt.value_or(std::nullopt));
    }

    inline void bind(QSqlQuery& query, const UpdateActivityDto& dto)
    {
        query.bindValue(":id", dto.id);
        query.bindValue(":application_id", dto.applicationId);
        query.bindValue(":ended_at", dto.endedAt);
    }
} // sun::persistence