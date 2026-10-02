#pragma once

#include "applicationlist/applicationlist.h"
#include "application/application.h"

#include <QList>

namespace sun::persistence
{
    class IApplicationListDao
    {
    public:
        ApplicationList create(const CreateApplicationListDto& dto) const;
        ApplicationList updateById(const UpdateApplicationListDto& dto) const;
        ApplicationList getById(int id) const;
        QList<ApplicationList> getAll() const;
        
        void addApplication(int listId, int applicationId) const;
        void removeApplication(int listId, int applicationId) const;
        void removeAllApplications(int listId) const;

        QList<Application> getAllApplications(int listId) const;

    private:
        virtual ApplicationList doCreate(const CreateApplicationListDto& dto) const = 0;
        virtual ApplicationList doUpdateById(const UpdateApplicationListDto& dto) const = 0;
        virtual ApplicationList doGetById(int id) const = 0;
        virtual QList<ApplicationList> doGetAll() const = 0;
        
        virtual void doAddApplication(int listId, int applicationId) const = 0;
        virtual void doRemoveApplication(int listId, int applicationId) const = 0;
        virtual void doRemoveAllApplications(int listId) const = 0;

        virtual QList<Application> doGetAllApplications(int listId) const = 0;
    };

    ApplicationList IApplicationListDao::create(const CreateApplicationListDto &dto) const
    {
        return doCreate(dto);
    }

    inline ApplicationList IApplicationListDao::updateById(const UpdateApplicationListDto &dto) const
    {
        return doUpdateById(dto);
    }

    inline ApplicationList IApplicationListDao::getById(int id) const
    {
        return doGetById(id);
    }

    inline QList<ApplicationList> IApplicationListDao::getAll() const
    {
        return doGetAll();
    }

    inline void IApplicationListDao::addApplication(int listId, int applicationId) const
    {
        doAddApplication(listId, applicationId);
    }

    inline void IApplicationListDao::removeApplication(int listId, int applicationId) const
    {
        doRemoveApplication(listId, applicationId);
    }

    inline void IApplicationListDao::removeAllApplications(int listId) const
    {
        doRemoveAllApplications(listId);
    }

    inline QList<Application> IApplicationListDao::getAllApplications(int listId) const
    {
        return doGetAllApplications(listId);
    }
} // sun::persistence