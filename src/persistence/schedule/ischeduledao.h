#pragma once

#include "schedule/schedule.h"
#include "applicationlist/applicationlist.h"

#include <QList>

namespace sun::persistence
{
    class IScheduleDao
    {
    public:
        Schedule create(const CreateScheduleDto& dto) const;
        Schedule updateById(const UpdateScheduleDto& dto) const;
        Schedule getById(int id) const;

        void deleteById(int id) const;
        
        QList<Schedule> getAll() const;

        void addApplicationList(int scheduleId, int listId) const;
        void removeApplicationList(int scheduleId, int listId) const;
        void removeAllApplicationLists(int scheduleId) const;

        QList<ApplicationList> getAllApplicationLists(int scheduleId) const;

    private:
        virtual Schedule doCreate(const CreateScheduleDto& dto) const = 0;
        virtual Schedule doUpdateById(const UpdateScheduleDto& dto) const = 0;
        virtual Schedule doGetById(int id) const = 0;

        virtual void doDeleteById(int id) const = 0;
        
        virtual QList<Schedule> doGetAll() const = 0;

        virtual void doAddApplicationList(int scheduleId, int listId) const = 0;
        virtual void doRemoveApplicationList(int scheduleId, int listId) const = 0;
        virtual void doRemoveAllApplicationLists(int scheduleId) const = 0;

        virtual QList<ApplicationList> doGetAllApplicationLists(int scheduleId) const = 0;
    };

    inline Schedule IScheduleDao::create(const CreateScheduleDto& dto) const
    {
        return doCreate(dto);
    }

    inline Schedule IScheduleDao::updateById(const UpdateScheduleDto &dto) const
    {
        return doUpdateById(dto);
    }

    inline Schedule IScheduleDao::getById(int id) const
    {
        return doGetById(id);
    }

    inline void IScheduleDao::deleteById(int id) const
    {
        return doDeleteById(id);
    }

    inline QList<Schedule> IScheduleDao::getAll() const
    {
        return doGetAll();
    }

    inline void IScheduleDao::addApplicationList(int scheduleId, int listId) const
    {
        doAddApplicationList(scheduleId, listId);
    }

    inline void IScheduleDao::removeApplicationList(int scheduleId, int listId) const
    {
        doRemoveApplicationList(scheduleId, listId);
    }

    inline void IScheduleDao::removeAllApplicationLists(int scheduleId) const
    {
        doRemoveAllApplicationLists(scheduleId);
    }

    inline QList<ApplicationList> IScheduleDao::getAllApplicationLists(int scheduleId) const
    {
        return doGetAllApplicationLists(scheduleId);
    }
} // sun::persistence