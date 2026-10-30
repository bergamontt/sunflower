#pragma once

#include "applicationlist/iapplicationlistservice.h"

namespace sun::core
{
    class ApplicationListService : public IApplicationListService
    {
    private:
        persistence::ApplicationList doCreate(const persistence::CreateApplicationListDto& dto) const override;
        persistence::ApplicationList doCreate(const persistence::CreateApplicationListDto& dto, const QList<int>& applicationIds) const override;
        persistence::ApplicationList doUpdateById(const persistence::UpdateApplicationListDto& dto) const override;
        persistence::ApplicationList doUpdateById(const persistence::UpdateApplicationListDto& dto, const QList<int>& applicationIds) const override;
        void doDeleteById(int id) const override;
        std::optional<persistence::ApplicationList> doGetById(int id) const override;
        QList<persistence::ApplicationList> doGetAll() const override;
        void doAddApplication(int listId, int applicationId) const override;
        void doRemoveApplication(int listId, int applicationId) const override;
        void doRemoveAllApplications(int listId) const override;
        QList<persistence::Application> doGetAllApplications(int listId) const override;
        persistence::ApplicationListDao applicationListDao;
    };
} // namespace sun::core

