#include "applicationservice.h"

namespace sun::core
{
    using namespace persistence;
  
    Application ApplicationService::doCreate(const CreateApplicationDto& dto) const
    {
        return applicationDao.create(dto);
    }
  
    QList<Application> ApplicationService::doCreate(const QList<CreateApplicationDto> &dtos) const
    {
        QList<Application> applications;
        for (const auto& dto : dtos)
        {
            Application application = doCreate(dto);
            applications.append(application);
        }
        return applications;
    }

    std::optional<Application> ApplicationService::doGetById(int id) const
    {
        return applicationDao.getById(id);
    }

    QList<Application> ApplicationService::doGetAll() const
    {
        return applicationDao.getAll();
    }

    Application ApplicationService::doUpdateById(const UpdateApplicationDto& dto) const
    {
        return applicationDao.updateById(dto);
    }

    void ApplicationService::doDeleteById(int id) const
    {
        applicationDao.deleteById(id);
    }
}
