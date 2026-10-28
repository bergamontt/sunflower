#pragma once

#include "applicationlistdao.h"

namespace sun::core
{
    class ApplicationListService
    {
    public:
        persistence::ApplicationList create(const persistence::CreateApplicationListDto& dto) const;
        persistence::ApplicationList updateById(const persistence::UpdateApplicationListDto& dto) const;
        void deleteById(int id) const;

        std::optional<persistence::ApplicationList> getById(int id) const;
        QList<persistence::ApplicationList> getAll() const;

        void addApplication(int listId, int applicationId) const;
        void removeApplication(int listId, int applicationId) const;
        void removeAllApplications(int listId) const;
        QList<persistence::Application> getAllApplications(int listId) const;

    private:
        persistence::ApplicationListDao applicationListDao;
    };
} // namespace sun::core

