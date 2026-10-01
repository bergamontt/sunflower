#include "application/applicationdao.h"
#include "application/applicationsql.h"
#include "application/applicationmapper.h"

#include <QSqlQuery>

namespace sun::persistence
{
    Application ApplicationDao::create(const CreateApplicationDto& dto)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application::create);
        ApplicationMapper::bind(query, dto);
        query.exec();
        return ApplicationMapper::toApplication(query);
    }

    Application ApplicationDao::updateById(const UpdateApplicationDto& dto)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application::update_by_id);
        ApplicationMapper::bind(query, dto);
        query.exec();
        return ApplicationMapper::toApplication(query);
    }

    Application ApplicationDao::getById(int id)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application::get_by_id);
        query.bindValue(":id", id);
        query.exec();
        return ApplicationMapper::toApplication(query);
    }

    void ApplicationDao::deleteById(int id)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application::delete_by_id);
        query.bindValue(":id", id);
        query.exec();
    }
} // sun::persistence