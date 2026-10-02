#include "application/applicationdao.h"
#include "application/applicationsql.h"
#include "application/applicationmapper.h"

#include <QSqlQuery>

namespace sun::persistence
{
    Application ApplicationDao::doCreate(const CreateApplicationDto& dto) const
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application::create);
        ApplicationMapper::bind(query, dto);
        query.exec();
        return ApplicationMapper::toApplication(query);
    }

    Application ApplicationDao::doUpdateById(const UpdateApplicationDto& dto) const
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application::update_by_id);
        ApplicationMapper::bind(query, dto);
        query.exec();
        return ApplicationMapper::toApplication(query);
    }

    Application ApplicationDao::doGetById(int id) const
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application::get_by_id);
        query.bindValue(":id", id);
        query.exec();
        return ApplicationMapper::toApplication(query);
    }

    void ApplicationDao::doDeleteById(int id) const
    {
        QSqlQuery query;
        query.prepare(sun::persistence::application::delete_by_id);
        query.bindValue(":id", id);
        query.exec();
    }
} // sun::persistence