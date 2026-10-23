#pragma once

#include "applicationlist/iapplicationlistdao.h"

#include <optional>

namespace sun::persistence
{
    class ApplicationListDao : public IApplicationListDao
    {
    private:
        ApplicationList doCreate(const CreateApplicationListDto& dto) const override;
        ApplicationList doUpdateById(const UpdateApplicationListDto& dto) const override;
        std::optional<ApplicationList> doGetById(int id) const override;
        
        void doDeleteById(int id) const override;

        QList<ApplicationList> doGetAll() const override;
        
        void doAddApplication(int listId, int applicationId) const override;
        void doRemoveApplication(int listId, int applicationId) const override;
        void doRemoveAllApplications(int listId) const override;

        QList<Application> doGetAllApplications(int listId) const override;
        QList<ApplicationList> doGetAllByApplication(int applicationId) const;
    };
}