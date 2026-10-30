#pragma once

#include "applicationlist/applicationlistdao.h"

namespace sun::core
{
    class IApplicationListService
    {
    public:
        persistence::ApplicationList create(const persistence::CreateApplicationListDto& dto) const;
        persistence::ApplicationList create(const persistence::CreateApplicationListDto& dto, const QList<int>& applicationIds) const;
        persistence::ApplicationList updateById(const persistence::UpdateApplicationListDto& dto) const;
        persistence::ApplicationList updateById(const persistence::UpdateApplicationListDto& dto, const QList<int>& applicationIds) const;
        void deleteById(int id) const;
        std::optional<persistence::ApplicationList> getById(int id) const;
        QList<persistence::ApplicationList> getAll() const;
        void addApplication(int listId, int applicationId) const;
        void removeApplication(int listId, int applicationId) const;
        void removeAllApplications(int listId) const;
        QList<persistence::Application> getAllApplications(int listId) const;
    private:
        virtual persistence::ApplicationList doCreate(const persistence::CreateApplicationListDto& dto) const = 0;
        virtual persistence::ApplicationList doCreate(const persistence::CreateApplicationListDto& dto, const QList<int>& applicationIds) const = 0;
        virtual persistence::ApplicationList doUpdateById(const persistence::UpdateApplicationListDto& dto) const = 0;
        virtual persistence::ApplicationList doUpdateById(const persistence::UpdateApplicationListDto& dto, const QList<int>& applicationIds) const = 0;
        virtual void doDeleteById(int id) const = 0;
        virtual std::optional<persistence::ApplicationList> doGetById(int id) const = 0;
        virtual QList<persistence::ApplicationList> doGetAll() const = 0;
        virtual void doAddApplication(int listId, int applicationId) const = 0;
        virtual void doRemoveApplication(int listId, int applicationId) const = 0;
        virtual void doRemoveAllApplications(int listId) const = 0;
        virtual QList<persistence::Application> doGetAllApplications(int listId) const = 0;
    };

    inline persistence::ApplicationList IApplicationListService::create(const persistence::CreateApplicationListDto& dto) const
    {
        return doCreate(dto);
    }

    inline persistence::ApplicationList IApplicationListService::create(const persistence::CreateApplicationListDto& dto, const QList<int>& applicationIds) const
    {
        return doCreate(dto, applicationIds);
    }

    inline persistence::ApplicationList IApplicationListService::updateById(const persistence::UpdateApplicationListDto& dto) const
    {
        return doUpdateById(dto);
    }

    inline persistence::ApplicationList IApplicationListService::updateById(const persistence::UpdateApplicationListDto& dto, const QList<int>& applicationIds) const
    {
        return doUpdateById(dto, applicationIds);
    }

    inline void IApplicationListService::deleteById(int id) const
    {
        doDeleteById(id);
    }

    inline std::optional<persistence::ApplicationList> IApplicationListService::getById(int id) const
    {
        return doGetById(id);
    }

    inline QList<persistence::ApplicationList> IApplicationListService::getAll() const
    {
        return doGetAll();
    }

    inline void IApplicationListService::addApplication(int listId, int applicationId) const
    {
        doAddApplication(listId, applicationId);
    }

    inline void IApplicationListService::removeApplication(int listId, int applicationId) const
    {
        doRemoveApplication(listId, applicationId);
    }

    inline void IApplicationListService::removeAllApplications(int listId) const
    {
        doRemoveAllApplications(listId);
    }

    inline QList<persistence::Application> IApplicationListService::getAllApplications(int listId) const
    {
        return doGetAllApplications(listId);
    }
}
