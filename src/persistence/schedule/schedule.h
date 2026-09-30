#pragma once

#include <QString>
#include <QTime>

#include <optional>

namespace sun::persistence
{
    struct Schedule
    {
        enum Type
        {
            TimeWindow,
            DailyLimit
        };

        enum LockType
        {
            None,
            Password,
            Delay
        };

        int id;
        QString name;
        Type type;
        QTime startsAt;
        QTime endsAt;
        int dailyLimit;
        int repeatAt;
        LockType lockType;
        QString lockHash;
        int unclockAfter;
        std::optional<QDateTime> unlockRequestedAt;
    };

    QString toString(const Schedule::Type type)
    {
        switch (type)
        {
            case Schedule::Type::TimeWindow:
                return "TIME_WINDOW";
            case Schedule::Type::DailyLimit:
                return "DAILY_LIMIT";
        }
    }

    Schedule::Type toType(const QString& str)
    {
        if (str == "TIME_WINDOW")
            return Schedule::Type::TimeWindow;
        return Schedule::Type::DailyLimit;
    }

    QString toString(const Schedule::LockType type)
    {
        switch (type)
        {
            case Schedule::LockType::Password:
                return "PASSWORD";
            case Schedule::LockType::Delay:
                return "DELAY";
            case Schedule::LockType::None:
                return "NONE";
        }
    }

    Schedule::LockType toLockType(const QString& str)
    {
        if (str == "PASSWORD")
            return Schedule::LockType::Password;
        else if (str == "DELAY")
            return Schedule::LockType::Delay;
        return Schedule::LockType::None;
    }
} // sun::persistence::schedule