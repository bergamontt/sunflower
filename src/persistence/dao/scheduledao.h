#pragma once

#include "../model/schedule.h"
#include "../model/applicationlist.h"

#include <QList>

namespace sun::persistence
{
    class ScheduleDao
    {
    public:
        Schedule create(const Schedule& schedule);
        Schedule updateById(int id, const Schedule& schedule);
        Schedule getById(int id);

        void deleteById(int id);
        
        QList<Schedule> getAll();

        void addApplicationList(int scheduleId, int listId);
        void removeApplicationList(int scheduleId, int listId);
        void removeAllApplicationLists(int scheduleId);

        QList<ApplicationList> getAllApplicationLists(int scheduleId);
    };
} // sun::persistence