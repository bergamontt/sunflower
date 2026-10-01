#include "applicationlist/applicationlistdao.h"
#include "applicationlist/applicationlistsql.h"
#include "applicationlist/applicationlistmapper.h"

#include "application/applicationmapper.h"

#include <QSqlQuery>
#include <QList>

namespace sun::persistence
{
    ApplicationList ApplicationListDao::create(const CreateApplicationListDto& dto)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application_list::create);
        ApplicationListMapper::bind(query, dto);
        query.exec();
        return ApplicationListMapper::toApplicationList(query);
    }

    ApplicationList ApplicationListDao::updateById(const UpdateApplicationListDto& dto)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application_list::update_by_id);
        ApplicationListMapper::bind(query, dto);
        query.exec();
        return ApplicationListMapper::toApplicationList(query);
    }

    ApplicationList ApplicationListDao::getById(int id)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application_list::get_by_id);
        query.bindValue(":id", id);
        query.exec();
        return ApplicationListMapper::toApplicationList(query);
    }

    QList<ApplicationList> ApplicationListDao::getAll()
    {
        QSqlQuery query;
        query.exec(sun::persistence::application_list::get_all);
        QList<ApplicationList> result;
        while (query.next())
        {
            result.append(ApplicationListMapper::toApplicationList(query));
        };
        return result;
    }

    void ApplicationListDao::addApplication(int listId, int applicationId)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application_list::add_application);
        query.bindValue(":application_list_id", listId);
        query.bindValue(":application_id", applicationId);
        query.exec();
    }

    void ApplicationListDao::removeApplication(int listId, int applicationId)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application_list::remove_application);
        query.bindValue(":application_list_id", listId);
        query.bindValue(":applciation_id", applicationId);
        query.exec();
    }

    void ApplicationListDao::removeAllApplications(int listId)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application_list::remove_all_applications);
        query.bindValue(":aplication_list_id", listId);
        query.exec();
    }

    QList<Application> ApplicationListDao::getAllApplications(int listId)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application_list::get_all_applications);
        query.bindValue(":application_list_id", listId);
        QList<Application> result;
        while (query.next()) 
        {
            result.append(ApplicationMapper::toApplication(query));
        }
        return result;
    }
} // sun::persistence