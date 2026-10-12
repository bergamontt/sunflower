#pragma once

#include <QDateTime>

#include <optional>

namespace sun::persistence
{
    struct Activity
    {
        int id;
        int applicationId;
        QDateTime startedAt;
        std::optional<QDateTime> endedAt;
    };

    struct CreateActivityDto
    {
        int applicationId;
        QDateTime startedAt;
        std::optional<QDateTime> endedAt;
    };

    struct UpdateActivityDto
    {
        int id;
        QDateTime endedAt;
    };

    inline bool operator==(const Activity& a, const Activity& b)
    {
        return a.id == b.id && a.applicationId == b.applicationId &&
            a.startedAt == b.startedAt && a.endedAt == b.endedAt;
    }
} // sun::persistence