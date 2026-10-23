
#pragma once

#include "applicationlistdao.h"

namespace sun::core
{
    class ApplicationListService
    {
    public:
        sun::persistence::ApplicationList create(const sun::persistence::CreateApplicationListDto& dto) const;
        sun::persistence::ApplicationList updateById(const sun::persistence::UpdateApplicationListDto& dto) const;
        std::optional<sun::persistence::ApplicationList> getById(int id) const;
        void deleteById(int id) const;
        QList<sun::persistence::ApplicationList> getAll() const;
        void addApplication(int listId, int applicationId) const;
        void removeApplication(int listId, int applicationId) const;
        void removeAllApplications(int listId) const;
        QList<sun::persistence::Application> getAllApplications(int listId) const;

    private:
        sun::persistence::ApplicationListDao applicationListDao;
    };
} // namespace sun::core

