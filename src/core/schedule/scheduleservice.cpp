#include "scheduleservice.h"
#include "applicationlist.h"

namespace sun::core
{
    using namespace persistence;

    Schedule ScheduleService::create(const CreateScheduleDto& dto) const
    {
        return scheduleDao.create(dto);
    }

    Schedule ScheduleService::updateById(const UpdateScheduleDto& dto) const
    {
        return scheduleDao.updateById(dto);
    }

        Schedule ScheduleService::updateById(const UpdateScheduleDto& dto, const QList<persistence::ApplicationList> newApplicationLists) const
    {
        const Schedule& newSchedule = scheduleDao.updateById(dto);

        const QList<ApplicationList>& oldApplicationLists = scheduleDao.getAllApplicationLists(newSchedule.id);
        for (const ApplicationList& oldApplicationList : oldApplicationLists)
        {
            bool shouldKeep = false;

            for (const ApplicationList& newApplicationList : newApplicationLists)
            {
                if (oldApplicationList.id == newApplicationList.id)
                {
                    shouldKeep = true;
                    break;
                }
            }

            if (!shouldKeep)
                scheduleDao.removeApplicationList(newSchedule.id, oldApplicationList.id);

            for (const ApplicationList& newApplicationList : newApplicationLists) {
                bool alreadyExists = false;

                for (const ApplicationList& oldApplicationList : oldApplicationLists)
                {
                    if (newApplicationList.id == oldApplicationList.id)
                    {
                        alreadyExists = true;
                        break;
                    }
                }

                if (!alreadyExists)
                    scheduleDao.addApplicationList(newSchedule.id, newApplicationList.id);
            }
        }
        
        return newSchedule;
    }

    Schedule ScheduleService::updateIsActiveById(int id, bool isActive) const
    {
        return scheduleDao.updateIsActiveById(id, isActive);
    }

    void ScheduleService::deleteById(int id) const
    {
        scheduleDao.deleteById(id);
    }

    std::optional<Schedule> ScheduleService::getById(int id) const
    {
        return scheduleDao.getById(id);
    }

    QList<Schedule> ScheduleService::getAll() const
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

    QList<ApplicationList> ScheduleService::getAllApplicationLists(int scheduleId) const
    {
        return scheduleDao.getAllApplicationLists(scheduleId);
    }
} // namespace sun::core
