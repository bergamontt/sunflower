#pragma once

#include "application/iapplicationdao.h"

#include <optional>

namespace sun::persistence
{
    class ApplicationDao : public IApplicationDao
    {
    private:
        Application doCreate(const CreateApplicationDto& dto) const override;
        Application doUpdateById(const UpdateApplicationDto& dto) const override;
        std::optional<Application> doGetById(int id) const override;
        void doDeleteById(int id) const override;
    };
} // sun::persistence