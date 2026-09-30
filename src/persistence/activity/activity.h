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
} // sun::persistence