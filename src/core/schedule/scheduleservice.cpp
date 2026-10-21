
#include "scheduleservice.h"

namespace sun::core
{
    sun::persistence::Schedule ScheduleService::create(const sun::persistence::CreateScheduleDto& dto) const
    {
        return scheduleDao.create(dto);
    }

    sun::persistence::Schedule ScheduleService::updateById(const sun::persistence::UpdateScheduleDto& dto) const
    {
        return scheduleDao.updateById(dto);
    }

    std::optional<sun::persistence::Schedule> ScheduleService::getById(int id) const
    {
        return scheduleDao.getById(id);
    }

    void ScheduleService::deleteById(int id) const
    {
        scheduleDao.deleteById(id);
    }

    QList<sun::persistence::Schedule> ScheduleService::getAll() const
    {
        return scheduleDao.getAll();
    }

    void ScheduleService::addApplicationList(int scheduleId, int listId) const
    {
        scheduleDao.addApplicationList(scheduleId, listId);
    }

    void ScheduleService::removeApplicationList(int scheduleId, int listId) const
    {
        scheduleDao.removeApplicationList(scheduleId, listId);
    }

    void ScheduleService::removeAllApplicationLists(int scheduleId) const
    {
        scheduleDao.removeAllApplicationLists(scheduleId);
    }

    QList<sun::persistence::ApplicationList> ScheduleService::getAllApplicationLists(int scheduleId) const
    {
        return scheduleDao.getAllApplicationLists(scheduleId);
    }
} // namespace sun::core
