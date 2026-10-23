#include "applicationservice.h"

namespace sun::core
{
    sun::persistence::Application ApplicationService::create(const sun::persistence::CreateApplicationDto& dto) const
    {
        return applicationDao.create(dto);
    }

    sun::persistence::Application ApplicationService::updateById(const sun::persistence::UpdateApplicationDto& dto) const
    {
        return applicationDao.updateById(dto);
    }

    std::optional<sun::persistence::Application> ApplicationService::getById(int id) const
    {
        return applicationDao.getById(id);
    }

    QList<sun::persistence::Application> ApplicationService::getAll() const
    {
        return applicationDao.getAll();
    }

    void ApplicationService::deleteById(int id) const
    {
        applicationDao.deleteById(id);
    }
}