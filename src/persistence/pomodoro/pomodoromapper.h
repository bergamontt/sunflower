#pragma once

#include "pomodoro/pomodoro.h"

#include <QSqlQuery>

namespace sun::persistence
{
    struct PomodoroMapper
    {
        static Pomodoro toPomodoro(const QSqlQuery& query);
        static void bind(QSqlQuery& query, const CreatePomodoroDto& dto);
        static void bind(QSqlQuery& query, const UpdatePomodoroDto& dto);
    };

    inline Pomodoro PomodoroMapper::toPomodoro(const QSqlQuery& query)
    {
        return 
        {
            query.value("id").toInt(),
            query.value("work_dauration").toInt(),
            query.value("break_duration").toInt(),
            query.value("ends_at").toDateTime(),
            toState(query.value("state").toString())
        };
    }
    
    inline void PomodoroMapper::bind(QSqlQuery& query, const CreatePomodoroDto& dto)
    {
        query.bindValue(":work_duration", dto.workDuration);
        query.bindValue(":break_duration", dto.breakDuration);
        query.bindValue(":ends_at", dto.endsAt);
        query.bindValue(":state", dto.state);
    }

    inline void PomodoroMapper::bind(QSqlQuery& query, const UpdatePomodoroDto& dto)
    {
        query.bindValue(":id", dto.id);
        query.bindValue(":work_duration", dto.workDuration);
        query.bindValue(":break_duration", dto.breakDuration);
        query.bindValue(":ends_at", dto.endsAt);
        query.bindValue(":state", dto.state);
    }
} // sun::persistence