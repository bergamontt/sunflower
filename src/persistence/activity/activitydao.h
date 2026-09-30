#pragma once

#include "activity/activity.h"

#include <QDateTime>

namespace sun::persistence
{
    class ActivityDao
    {
    public:
        Activity create(Activity& activity);
        Activity updateEndedAt(int id, QDateTime& endedAt);
        Activity getById(int id);
        void deleteById(int id);
    };
} // sun::persistence
