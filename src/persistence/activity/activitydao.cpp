#include "activity/activitydao.h"
#include "activity/activitysql.h"
#include "activity/activitymapper.h"

#include <QSqlQuery>
#include <QString>

namespace sun::persistence
{
    Activity ActivityDao::doCreate(const CreateActivityDto& dto) const
    {
        QSqlQuery query;
        query.prepare(sun::persistence::activity::create);
        ActivityMapper::bind(query, dto);
        query.exec();
        return ActivityMapper::toActivity(query);
    }

    Activity ActivityDao::doUpdateGetById(const UpdateActivityDto& dto) const
    {
        QSqlQuery query;
        query.prepare(sun::persistence::activity::update_ended_at);
        ActivityMapper::bind(query, dto);
        query.exec();
        return ActivityMapper::toActivity(query);
    }

    Activity ActivityDao::doGetById(int id) const
    {
        QSqlQuery query;
        query.prepare(sun::persistence::activity::get_by_id);
        query.bindValue(":id", id);
        query.exec();
        return ActivityMapper::toActivity(query);
    }

    void ActivityDao::doDeleteById(int id) const
    {
        QSqlQuery query;
        query.prepare(sun::persistence::activity::delete_by_id);
        query.bindValue(":id", id);
        query.exec();
    }
} // sun::persistence