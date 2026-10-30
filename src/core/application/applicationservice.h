#pragma once

#include "application/iapplicationservice.h"

namespace sun::core
{
    class ApplicationService : public IApplicationService
    {
    private:
        persistence::Application doCreate(const persistence::CreateApplicationDto& dto) const override;
        QList<persistence::Application> doCreate(const QList<persistence::CreateApplicationDto>& dtos) const override;
        std::optional<persistence::Application> doGetById(int id) const override;
        QList<persistence::Application> doGetAll() const override;
        persistence::Application doUpdateById(const persistence::UpdateApplicationDto& dto) const override;
        void doDeleteById(int id) const override;
        persistence::ApplicationDao applicationDao;
    };
} // sun::core
