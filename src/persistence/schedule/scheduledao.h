#pragma once

#include "schedule/ischeduledao.h"

namespace sun::persistence
{
    class ScheduleDao : public IScheduleDao
    {
    private:
        Schedule doCreate(const CreateScheduleDto& dto) const override;
        Schedule doUpdateById(const UpdateScheduleDto& dto) const override;
        Schedule doGetById(int id) const override;

        void doDeleteById(int id) const override;
        
        QList<Schedule> doGetAll() const override;

        void doAddApplicationList(int scheduleId, int listId) const override;
        void doRemoveApplicationList(int scheduleId, int listId) const override;
        void doRemoveAllApplicationLists(int scheduleId) const override;

        QList<ApplicationList> doGetAllApplicationLists(int scheduleId) const override;
    };
} // sun::persistence