#pragma once
#include <QString>
#include <QTime>
#include <optional>

namespace sun::persistence::schedule
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
} // sun::persistence::schedule