#pragma once

#include "application/iapplicationdao.h"

namespace sun::persistence
{
    class ApplicationDao : IApplicationDao
    {
    private:
        Application doCreate(const CreateApplicationDto& dto) const override;
        Application doUpdateById(const UpdateApplicationDto& dto) const override;
        Application doGetById(int id) const override;
        void doDeleteById(int id) const override;
    };
} // sun::persistence