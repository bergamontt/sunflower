#pragma once

#include "application/applicationdao.h"

#include <QList>

namespace sun::core
{
    class ApplicationService
    {
    public:
        persistence::Application create(const persistence::CreateApplicationDto& dto) const;
        QList<persistence::Application> create(const QList<persistence::CreateApplicationDto>& dtos) const;
      
        std::optional<persistence::Application> getById(int id) const;
        QList<persistence::Application> getAll() const;
      
        persistence::Application updateById(const persistence::UpdateApplicationDto& dto) const;
        void deleteById(int id) const;
      
    private:
        persistence::ApplicationDao applicationDao;
    };
} // sun::core
