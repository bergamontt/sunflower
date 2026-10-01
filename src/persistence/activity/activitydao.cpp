#include "activity/activitydao.h"
#include "activity/activitysql.h"
#include "activity/activitymapper.h"

#include <QSqlQuery>
#include <QString>

namespace sun::persistence
{
    Activity ActivityDao::create(const CreateActivityDto& dto)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::activity::create);
        ActivityMapper::bind(query, dto);
        query.exec();
        return ActivityMapper::toActivity(query);
    }

    Activity ActivityDao::updateEndedAt(int id, UpdateActivityDto& dto)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::activity::update_ended_at);
        query.bindValue(":id", id);
        ActivityMapper::bind(query, dto);
        query.exec();
        return ActivityMapper::toActivity(query);
    }

    Activity ActivityDao::getById(int id)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::activity::get_by_id);
        query.bindValue(":id", id);
        query.exec();
        return ActivityMapper::toActivity(query);
    }

    void ActivityDao::deleteById(int id)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::activity::delete_by_id);
        query.bindValue(":id", id);
        query.exec();
    }
} // sun::persistence