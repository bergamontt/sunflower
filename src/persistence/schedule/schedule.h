#pragma once

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

        enum Day
        {
            MON = 0b0000001,
            TUE = 0b0000010,
            WED = 0b0000100,
            THU = 0b0001000,
            FRI = 0b0010000,
            SAT = 0b0100000,
            SUN = 0b1000000
        };

        int id;
        QString name;

        Type type;
        LockType lockType;

        int id;
        QString name;
        Type type;
        int repeatAt;

        std::optional<QTime> startsAt;
        std::optional<QTime> endsAt;
        std::optional<int> dailyLimit;
    };

    struct CreateScheduleDto
    {
        QString name;

        Schedule::Type type;
        
        int repeatAt;

        std::optional<QTime> startsAt;
        std::optional<QTime> endsAt;
        std::optional<int> dailyLimit;
    };

    struct UpdateScheduleDto
    {
        int id;
        QString name;
        Schedule::Type type;
        int repeatAt;

        std::optional<QTime> startsAt;
        std::optional<QTime> endsAt;
        std::optional<int> dailyLimit;
    };

    inline QString toString(const Schedule::Type type)
    {
        switch (type)
        {
            case Schedule::Type::TimeWindow:
                return "TIME_WINDOW";
            case Schedule::Type::DailyLimit:
                return "DAILY_LIMIT";
        }
        return "DAILY_LIMIT";
    }

    inline Schedule::Type toType(const QString& str)
    {
        if (str == "TIME_WINDOW")
            return Schedule::Type::TimeWindow;
        return Schedule::Type::DailyLimit;
    }

    inline bool operator==(const Schedule& a, const Schedule& b)
    {
        return a.id == b.id && a.name == b.name && a.type == b.type &&
            a.repeatAt == b.repeatAt && a.startsAt == b.startsAt &&
            a.endsAt == b.endsAt && a.dailyLimit == b.dailyLimit;
    }

} // sun::persistence::schedule