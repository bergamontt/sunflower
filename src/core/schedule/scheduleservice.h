#pragma once

#include "applicationlist.h"
#include "schedule/scheduledao.h"

namespace sun::core
{
    class ScheduleService
    {
    public:
        persistence::Schedule create(const persistence::CreateScheduleDto& dto) const;
        persistence::Schedule updateById(const persistence::UpdateScheduleDto& dto) const;
        persistence::Schedule updateById(const persistence::UpdateScheduleDto& dto, const QList<persistence::ApplicationList> newApplicationLists) const;
        persistence::Schedule updateIsActiveById(int id, bool isActive) const;
        void deleteById(int id) const;

        std::optional<persistence::Schedule> getById(int id) const;
        QList<persistence::Schedule> getAll() const;
        
        void addApplicationList(int scheduleId, int listId) const;
        void removeApplicationList(int scheduleId, int listId) const;
        void removeAllApplicationLists(int scheduleId) const;
        QList<persistence::Schedule> getAllByApplicationList(int listId) const;
        QList<persistence::ApplicationList> getAllApplicationLists(int scheduleId) const;

    private:
        persistence::ScheduleDao scheduleDao;
    };
} // namespace sun::core

