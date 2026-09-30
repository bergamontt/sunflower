#pragma once

#include "pomodoro/pomodoro.h"

#include <QSqlQuery>

namespace sun::persistence
{
    struct PomodoroMapper
    {
        static Pomodoro toPomodoro(const QSqlQuery& query);
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
} // sun::persistence