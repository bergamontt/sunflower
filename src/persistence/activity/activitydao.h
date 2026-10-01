#pragma once

#include "activity/activity.h"

#include <QDateTime>

namespace sun::persistence
{
    class ActivityDao
    {
    public:
        Activity create(const CreateActivityDto& dto);
        Activity updateEndedAt(int id, UpdateActivityDto& dto);
        Activity getById(int id);
        void deleteById(int id);
    };
} // sun::persistence
