#include "applicationlistservice.h"

namespace sun::core
{
    using namespace persistence;

    ApplicationList ApplicationListService::create(const CreateApplicationListDto& dto) const
    {
        return applicationListDao.create(dto);
    }

    std::optional<ApplicationList> ApplicationListService::getById(int id) const
    {
        return applicationListDao.getById(id);
    }

    QList<ApplicationList> ApplicationListService::getAll() const
    {
        return applicationListDao.getAll();
    }

    ApplicationList ApplicationListService::updateById(const UpdateApplicationListDto& dto) const
    {
        return applicationListDao.updateById(dto);
    }

    void ApplicationListService::deleteById(int id) const
    {
        applicationListDao.deleteById(id);
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

    QList<Application> ApplicationListService::getAllApplications(int listId) const
    {
        return applicationListDao.getAllApplications(listId);
    }
} // namespace sun::core
