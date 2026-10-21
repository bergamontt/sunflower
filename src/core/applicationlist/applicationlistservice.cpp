
#include "applicationlistservice.h"
#include "applicationlist.h"

namespace sun::core
{
    using sun::persistence::ApplicationList;

    ApplicationList ApplicationListService::create(const sun::persistence::CreateApplicationListDto& dto) const
    {
        return applicationListDao.create(dto);
    }

    ApplicationList ApplicationListService::updateById(const sun::persistence::UpdateApplicationListDto& dto) const
    {
        return applicationListDao.updateById(dto);
    }

    std::optional<ApplicationList> ApplicationListService::getById(int id) const
    {
        return applicationListDao.getById(id);
    }

    void ApplicationListService::deleteById(int id) const
    {
        applicationListDao.deleteById(id);
    }

    QList<ApplicationList> ApplicationListService::getAll() const
    {
        return applicationListDao.getAll();
    }

    void ApplicationListService::addApplication(int listId, int applicationId) const
    {
        applicationListDao.addApplication(listId, applicationId);
    }

    void ApplicationListService::removeApplication(int listId, int applicationId) const
    {
        applicationListDao.removeApplication(listId, applicationId);
    }

    void ApplicationListService::removeAllApplications(int listId) const
    {
        applicationListDao.removeAllApplications(listId);
    }

    QList<sun::persistence::Application> ApplicationListService::getAllApplications(int listId) const
    {
        return applicationListDao.getAllApplications(listId);
    }
} // namespace sun::core
