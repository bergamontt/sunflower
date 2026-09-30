#include "schedule/scheduledao.h"
#include "schedule/schedulesql.h"
#include "schedule/schedulemapper.h"

#include "applicationlist/applicationlistmapper.h"

#include <QSqlQuery>

namespace sun::persistence
{
    Schedule ScheduleDao::create(const Schedule& schedule)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::schedule::create);
        query.bindValue(":name", schedule.name);
        query.bindValue(":type", toString(schedule.type));
        query.bindValue(":starts_at", schedule.startsAt);
        query.bindValue(":ends_at", schedule.endsAt);
        query.bindValue(":daily_limit", schedule.dailyLimit);
        query.bindValue(":repeat_at", schedule.repeatAt);
        query.bindValue(":lock_type", toString(schedule.lockType));
        query.bindValue(":lock_hash", schedule.lockHash);
        query.bindValue(":unlock_after", schedule.unclockAfter);
        query.bindValue(":unlock_requested_at", schedule.unlockRequestedAt.value_or(std::nullopt));
        query.exec();
        return ScheduleMapper::toSchedule(query);
    }

    Schedule ScheduleDao::updateById(int id, const Schedule &schedule)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::schedule::update_by_id);
        query.bindValue(":name", schedule.name);
        query.bindValue(":type", toString(schedule.type));
        query.bindValue(":starts_at", schedule.startsAt);
        query.bindValue(":ends_at", schedule.endsAt);
        query.bindValue(":daily_limit", schedule.dailyLimit);
        query.bindValue(":repeat_at", schedule.repeatAt);
        query.bindValue(":lock_type", toString(schedule.lockType));
        query.bindValue(":lock_hash", schedule.lockHash);
        query.bindValue(":unlock_after", schedule.unclockAfter);
        query.bindValue(":unlock_requested_at", schedule.unlockRequestedAt.value_or(std::nullopt));
        query.exec();
        return ScheduleMapper::toSchedule(query);
    }

    Schedule ScheduleDao::getById(int id)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::schedule::get_by_id);
        query.bindValue(":id", id);
        query.exec();
        return ScheduleMapper::toSchedule(query);
    }

    void ScheduleDao::deleteById(int id)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::schedule::delete_by_id);
        query.bindValue(":id", id);
        query.exec();
    }

    QList<Schedule> ScheduleDao::getAll()
    {
        QSqlQuery query;
        query.exec(sun::persistence::schedule::get_all);
        QList<Schedule> result;
        while(query.next())
        {
            result.append(ScheduleMapper::toSchedule(query));
        }
        return result;
    }

    void ScheduleDao::addApplicationList(int scheduleId, int listId)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::schedule::add_application_list);
        query.bindValue(":schedule_id", scheduleId);
        query.bindValue("application_list_id", listId);
        query.exec();
    }

    void ScheduleDao::removeApplicationList(int scheduleId, int listId)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::schedule::remove_application_list);
        query.bindValue(":schedule_id", scheduleId);
        query.bindValue("application_list_id", listId);
        query.exec();
    }

    void ScheduleDao::removeAllApplicationLists(int scheduleId)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::schedule::remove_all_application_lists);
        query.bindValue(":schedule_id", scheduleId);
        query.exec();
    }

    QList<ApplicationList> ScheduleDao::getAllApplicationLists(int scheduleId)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::schedule::get_all_application_lists);
        query.bindValue(":schedule_id", scheduleId);
        query.exec();
        QList<ApplicationList> result;
        while (query.next())
        {
            result.append(ApplicationListMapper::toApplicationList(query));
        }
        return result;
    }
} // sun::persistence