#include "activitydao.h"
#include "activitysql.h"

#include <QSqlQuery>
#include <QString>

namespace sun::persistence
{
    Activity ActivityDao::create(Activity &activity)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::activity::create);
        query.bindValue(":application_id", activity.applicationId);
        query.bindValue(":started_at", activity.startedAt);
        if (activity.endedAt.has_value())
        {
            query.bindValue(":ended_at", activity.endedAt.value());
        }
        query.exec();
        return
        {
            query.value("id").toInt(),
            query.value("application_id").toInt(),
            query.value("started_at").toDateTime(),
            query.value("ended_at").toDateTime()
        };
    }

    Activity ActivityDao::updateEndedAt(int id, QDateTime& endedAt)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::activity::update_ended_at);
        query.bindValue(":id", id);
        query.bindValue(":ended_at", endedAt);
        query.exec();
        return
        {
            query.value("id").toInt(),
            query.value("application_id").toInt(),
            query.value("started_at").toDateTime(),
            query.value("ended_at").toDateTime()
        };
    }

    Activity ActivityDao::getById(int id)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::activity::get_by_id);
        query.bindValue(":id", id);
        query.exec();
        return
        {
            query.value("id").toInt(),
            query.value("application_id").toInt(),
            query.value("started_at").toDateTime(),
            query.value("ended_at").toDateTime()
        };
    }

    void ActivityDao::deleteById(int id)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::activity::delete_by_id);
        query.bindValue(":id", id);
        query.exec();
    }
} // sun::persistence