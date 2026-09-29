#include "applicationdao.h"

#include "../sql/applicationsql.h"

#include <QSqlQuery>

namespace sun::persistence
{
    Application ApplicationDao::create(const Application& application)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application::create);
        query.bindValue(":name", application.name);
        query.bindValue(":process_name", application.processName);
        query.exec();
        return 
        {
            query.value("id").toInt(),
            query.value("name").toString(),
            query.value("process_name").toString()
        };
    }

    Application ApplicationDao::updateById(int id, const Application& application)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application::update_by_id);
        query.bindValue(":name", application.name);
        query.bindValue(":process_name", application.processName);
        query.exec();
        return 
        {
            query.value("id").toInt(),
            query.value("name").toString(),
            query.value("process_name").toString()
        };
    }

    Application ApplicationDao::getById(int id)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application::get_by_id);
        query.bindValue(":id", id);
        query.exec();
        return 
        {
            query.value("id").toInt(),
            query.value("name").toString(),
            query.value("process_name").toString()
        };
    }

    void ApplicationDao::deleteById(int id)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application::delete_by_id);
        query.bindValue(":id", id);
        query.exec();
    }
} // sun::persistence