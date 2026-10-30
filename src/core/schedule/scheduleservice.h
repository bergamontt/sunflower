#pragma once

#include "schedule/ischeduledservice.h"

namespace sun::core
{
    class ScheduleService : public IScheduleService
    {
    private:
        persistence::Schedule doCreate(const persistence::CreateScheduleDto& dto) const override;
        persistence::Schedule doUpdateById(const persistence::UpdateScheduleDto& dto) const override;
        persistence::Schedule doUpdateById(const persistence::UpdateScheduleDto& dto, const QList<persistence::ApplicationList> newApplicationLists) const override;
        persistence::Schedule doUpdateIsActiveById(int id, bool isActive) const override;
        void doDeleteById(int id) const override;
        std::optional<persistence::Schedule> doGetById(int id) const override;
        QList<persistence::Schedule> doGetAll() const override;
        void doAddApplicationList(int scheduleId, int listId) const override;
        void doRemoveApplicationList(int scheduleId, int listId) const override;
        void doRemoveAllApplicationLists(int scheduleId) const override;
        QList<persistence::Schedule> doGetAllByApplicationList(int listId) const override;
        QList<persistence::ApplicationList> doGetAllApplicationLists(int scheduleId) const override;
        persistence::ScheduleDao scheduleDao;
    };
} // namespace sun::core

