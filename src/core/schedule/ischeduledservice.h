#pragma once

#include "schedule/scheduledao.h"

namespace sun::core
{
    class IScheduleService
    {
    public:
        virtual ~IScheduleService() = default;
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
        virtual persistence::Schedule doCreate(const persistence::CreateScheduleDto& dto) const = 0;
        virtual persistence::Schedule doUpdateById(const persistence::UpdateScheduleDto& dto) const = 0;
        virtual persistence::Schedule doUpdateById(const persistence::UpdateScheduleDto& dto, const QList<persistence::ApplicationList> newApplicationLists) const = 0;
        virtual persistence::Schedule doUpdateIsActiveById(int id, bool isActive) const = 0;
        virtual void doDeleteById(int id) const = 0;
        virtual std::optional<persistence::Schedule> doGetById(int id) const = 0;
        virtual QList<persistence::Schedule> doGetAll() const = 0;
        virtual void doAddApplicationList(int scheduleId, int listId) const = 0;
        virtual void doRemoveApplicationList(int scheduleId, int listId) const = 0;
        virtual void doRemoveAllApplicationLists(int scheduleId) const = 0;
        virtual QList<persistence::Schedule> doGetAllByApplicationList(int listId) const = 0;
        virtual QList<persistence::ApplicationList> doGetAllApplicationLists(int scheduleId) const = 0;
    };

    inline persistence::Schedule IScheduleService::create(const persistence::CreateScheduleDto& dto) const
    {
        return doCreate(dto);
    }

    inline persistence::Schedule IScheduleService::updateById(const persistence::UpdateScheduleDto& dto) const
    {
        return doUpdateById(dto);
    }

    inline persistence::Schedule IScheduleService::updateById(const persistence::UpdateScheduleDto& dto, const QList<persistence::ApplicationList> newApplicationLists) const
    {
        return doUpdateById(dto, newApplicationLists);
    }

    inline persistence::Schedule IScheduleService::updateIsActiveById(int id, bool isActive) const
    {
        return doUpdateIsActiveById(id, isActive);
    }

    inline void IScheduleService::deleteById(int id) const
    {
        doDeleteById(id);
    }

    inline std::optional<persistence::Schedule> IScheduleService::getById(int id) const
    {
        return doGetById(id);
    }

    inline QList<persistence::Schedule> IScheduleService::getAll() const
    {
        return doGetAll();
    }

    inline void IScheduleService::addApplicationList(int scheduleId, int listId) const
    {
        doAddApplicationList(scheduleId, listId);
    }

    inline void IScheduleService::removeApplicationList(int scheduleId, int listId) const
    {
        doRemoveApplicationList(scheduleId, listId);
    }

    inline void IScheduleService::removeAllApplicationLists(int scheduleId) const
    {
        doRemoveAllApplicationLists(scheduleId);
    }

    inline QList<persistence::Schedule> IScheduleService::getAllByApplicationList(int listId) const
    {
        return doGetAllByApplicationList(listId);
    }

    inline QList<persistence::ApplicationList> IScheduleService::getAllApplicationLists(int scheduleId) const
    {
        return doGetAllApplicationLists(scheduleId);
    }
}
