#pragma once

#include "application/applicationdao.h"

namespace sun::core
{
    class ApplicationService
    {
    public:
        sun::persistence::Application create(const sun::persistence::CreateApplicationDto& dto) const;
        sun::persistence::Application updateById(const sun::persistence::UpdateApplicationDto& dto) const;
        std::optional<sun::persistence::Application> getById(int id) const;
        QList<sun::persistence::Application> getAll() const;
        void deleteById(int id) const;

    private:
        sun::persistence::ApplicationDao applicationDao;
    };
}