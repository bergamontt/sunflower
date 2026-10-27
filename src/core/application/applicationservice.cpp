#include "application/applicationservice.h"

namespace sun::core
{
    using namespace persistence;

    Application ApplicationService::create(const CreateApplicationDto &dto)
    {
        return applicationDao.create(dto);
    }

    QList<Application> ApplicationService::create(const QList<CreateApplicationDto> &dtos)
    {
        QList<Application> applications;
        for (const auto& dto : dtos)
        {
            Application application = create(dto);
            applications.append(application);
        }
        return applications;
    }
}