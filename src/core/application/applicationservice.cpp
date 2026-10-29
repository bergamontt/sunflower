#include "applicationservice.h"

namespace sun::core
{
    using namespace persistence;
  
    Application ApplicationService::create(const CreateApplicationDto& dto) const
    {
        return applicationDao.create(dto);
    }
  
    QList<Application> ApplicationService::create(const QList<CreateApplicationDto> &dtos) const
    {
        QList<Application> applications;
        for (const auto& dto : dtos)
        {
            Application application = create(dto);
            applications.append(application);
        }
        return applications;
    }

    std::optional<Application> ApplicationService::getById(int id) const
    {
        return applicationDao.getById(id);
    }

    QList<Application> ApplicationService::getAll() const
    {
        return applicationDao.getAll();
    }

    Application ApplicationService::updateById(const UpdateApplicationDto& dto) const
    {
        return applicationDao.updateById(dto);
    }

    void ApplicationService::deleteById(int id) const
    {
        applicationDao.deleteById(id);
    }
}