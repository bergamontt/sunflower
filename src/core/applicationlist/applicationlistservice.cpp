#include "applicationlistservice.h"

namespace sun::core
{
    using namespace persistence;

    ApplicationList ApplicationListService::create(const CreateApplicationListDto& dto) const
    {
        return applicationListDao.create(dto);
    }

    ApplicationList ApplicationListService::create(const CreateApplicationListDto& dto, const QList<int>& applicationIds) const
    {
        const ApplicationList& applicationList = applicationListDao.create(dto);
        for(const int applicationId : applicationIds)
        {
            applicationListDao.addApplication(applicationList.id, applicationId);
        }
        return applicationList;
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

    ApplicationList ApplicationListService::updateById(const UpdateApplicationListDto& dto, const QList<int>& applicationIds) const
    {
        const ApplicationList& applicationList = applicationListDao.updateById(dto);
        const QList<Application>& oldApplications = applicationListDao.getAllApplications(applicationList.id);

        for (const Application& application : oldApplications)
        {
            if (!applicationIds.contains(application.id))
                applicationListDao.removeApplication(applicationList.id, application.id);
        }

        for (int applicationId : applicationIds)
        {
            bool exists = false;

            for (const Application& application : oldApplications)
            {
                if (application.id == applicationId)
                {
                    exists = true;
                    break;
                }
            }

            if (!exists)
                applicationListDao.addApplication(applicationList.id, applicationId);
        }

        return applicationList;
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
