#pragma once
#include <QDateTime>

namespace sun::persistence
{
    struct Pomodoro
    {
        enum State
        {
            Work,
            Break,
            Paused,
            Inactive
        };

        int id;
        int workDuration;
        int breakDuration;
        QDateTime endsAt;
        State state;
    };
} // sun::persistence::pomdoro