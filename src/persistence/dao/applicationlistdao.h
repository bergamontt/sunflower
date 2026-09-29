#pragma once

#include "../model/applicationlist.h"
#include "../model/application.h"

#include <QList>

namespace sun::persistence
{
    class ApplicationListDao
    {
    public:
        ApplicationList create(const ApplicationList& list);
        ApplicationList getById(int id);
        QList<ApplicationList> getAll();
        
        void addApplication(int listId, int applicationId);
        void removeApplication(int listId, int applicationId);
        void removeAllApplications(int listId);
        QList<Application> getAllApplications(int listId);
    };
} // sun::persistence