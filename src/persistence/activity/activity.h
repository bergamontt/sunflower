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
        int applicationId;
        QDateTime endedAt;
    };
} // sun::persistence