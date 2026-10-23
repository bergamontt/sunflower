
#pragma once

#include "schedule/scheduledao.h"

namespace sun::core
{
    class ScheduleService
    {
    public:
        sun::persistence::Schedule create(const sun::persistence::CreateScheduleDto& dto) const;
        sun::persistence::Schedule updateById(const sun::persistence::UpdateScheduleDto& dto) const;
        sun::persistence::Schedule updateIsActiveById(int id, bool isActive) const;
        std::optional<sun::persistence::Schedule> getById(int id) const;
        void deleteById(int id) const;
        QList<sun::persistence::Schedule> getAll() const;
        void addApplicationList(int scheduleId, int listId) const;
        void removeApplicationList(int scheduleId, int listId) const;
        void removeAllApplicationLists(int scheduleId) const;
        QList<sun::persistence::ApplicationList> getAllApplicationLists(int scheduleId) const;

    private:
        sun::persistence::ScheduleDao scheduleDao;
    };
} // namespace sun::core

