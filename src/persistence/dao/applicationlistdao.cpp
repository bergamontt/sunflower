#include "applicationlistdao.h"

#include "../sql/applicationlistsql.h"

#include <QSqlQuery>
#include <QList>

namespace sun::persistence
{
    ApplicationList ApplicationListDao::create(const ApplicationList &list)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application_list::create);
        if (list.name.has_value())
        {
            query.bindValue(":name", list.name.value());
        }
        query.exec();
        return
        {
            query.value("id").toInt(),
            query.value("name").toString()
        };
    }

    ApplicationList ApplicationListDao::getById(int id)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application_list::get_by_id);
        query.bindValue(":id", id);
        query.exec();
        return 
        {
            query.value("id").toInt(),
            query.value("name").toString()
        };
    }

    QList<ApplicationList> ApplicationListDao::getAll()
    {
        QSqlQuery query;
        query.exec(sun::persistence::application_list::get_all);
        QList<ApplicationList> result;
        while (query.next())
        {
            result.append({
                query.value("id").toInt(),
                query.value("name").toString()
            });
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
            result.append({
                query.value("id").toInt(),
                query.value("name").toString(),
                query.value("process_name").toString()
            });
        }
        return result;
    }
} // sun::persistence