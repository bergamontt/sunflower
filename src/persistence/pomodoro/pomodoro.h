#pragma once

#include <QDateTime>
#include <QString>

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

    struct CreatePomodoroDto
    {
        int workDuration;
        int breakDuration;
        QDateTime endsAt;
        Pomodoro::State state;
    };

    struct UpdatePomodoroDto
    {
        int id;
        int workDuration;
        int breakDuration;
        QDateTime endsAt;
        Pomodoro::State state;
    };

    inline QString toString(const Pomodoro::State state)
    {
        switch (state)
        {
            case Pomodoro::State::Work:
                return "WORK";
            case Pomodoro::State::Break:
                return "BREAK";
            case Pomodoro::State::Inactive:
                return "INACTIVE";
            case Pomodoro::State::Paused:
                return "PAUSED";
        }
        return "INACTIVE";
    }

    inline Pomodoro::State toState(const QString& str)
    {
        if (str == "WORK")
            return Pomodoro::State::Work;
        if (str == "BREAK")
            return Pomodoro::State::Break;
        if (str == "PAUSED")
            return Pomodoro::State::Paused;
        return Pomodoro::State::Inactive;
    }

    inline bool operator==(const Pomodoro& a, const Pomodoro& b)
    {
        return a.id == b.id && a.workDuration == b.workDuration &&
            a.breakDuration == b.breakDuration && a.endsAt == b.endsAt &&
            a.state == b.state;
    }
} // sun::persistence::pomodoro