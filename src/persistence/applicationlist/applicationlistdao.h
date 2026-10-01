#pragma once

#include "applicationlist/applicationlist.h"
#include "application/application.h"

#include <QList>

namespace sun::persistence
{
    class ApplicationListDao
    {
    public:
        ApplicationList create(const CreateApplicationListDto& dto);
        ApplicationList updateById(const UpdateApplicationListDto& dto);
        ApplicationList getById(int id);
        QList<ApplicationList> getAll();
        
        void addApplication(int listId, int applicationId);
        void removeApplication(int listId, int applicationId);
        void removeAllApplications(int listId);

        QList<Application> getAllApplications(int listId);
    };
} // sun::persistence