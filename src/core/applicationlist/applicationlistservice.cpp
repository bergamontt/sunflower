#include "applicationlistservice.h"

namespace sun::core
{
    using namespace persistence;

    ApplicationList ApplicationListService::doCreate(const CreateApplicationListDto& dto) const
    {
        return applicationListDao.create(dto);
    }

    ApplicationList ApplicationListService::doCreate(const CreateApplicationListDto& dto, const QList<int>& applicationIds) const
    {
        const ApplicationList& applicationList = applicationListDao.create(dto);
        for(const int applicationId : applicationIds)
        {
            applicationListDao.addApplication(applicationList.id, applicationId);
        }
        return applicationList;
    }

    std::optional<ApplicationList> ApplicationListService::doGetById(int id) const
    {
        return applicationListDao.getById(id);
    }

    QList<ApplicationList> ApplicationListService::doGetAll() const
    {
        return applicationListDao.getAll();
    }

    ApplicationList ApplicationListService::doUpdateById(const UpdateApplicationListDto& dto) const
    {
        return applicationListDao.updateById(dto);
    }

    ApplicationList ApplicationListService::doUpdateById(const UpdateApplicationListDto& dto, const QList<int>& applicationIds) const
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


    void ApplicationListService::doDeleteById(int id) const
    {
        applicationListDao.removeAllApplications(id);
        applicationListDao.deleteById(id);
    }

    void ApplicationListService::doAddApplication(int listId, int applicationId) const
    {
        applicationListDao.addApplication(listId, applicationId);
    }

    void ApplicationListService::doRemoveApplication(int listId, int applicationId) const
    {
        applicationListDao.removeApplication(listId, applicationId);
    }

    void ApplicationListService::doRemoveAllApplications(int listId) const
    {
        applicationListDao.removeAllApplications(listId);
    }

    QList<Application> ApplicationListService::doGetAllApplications(int listId) const
    {
        return applicationListDao.getAllApplications(listId);
    }
} // namespace sun::core
