#include "schedule/scheduledao.h"
#include "schedule/schedulesql.h"
#include "schedule/schedulemapper.h"

#include "applicationlist/applicationlistmapper.h"

#include <QSqlQuery>

namespace sun::persistence
{
    Schedule ScheduleDao::doCreate(const CreateScheduleDto& dto) const
    {
        QSqlQuery query;
        query.prepare(sun::persistence::schedule::create);
        ScheduleMapper::bind(query, dto);
        query.exec();
        query.next();
        return ScheduleMapper::toSchedule(query);
    }

    Schedule ScheduleDao::doUpdateById(const UpdateScheduleDto& dto) const
    {
        QSqlQuery query;
        query.prepare(sun::persistence::schedule::update_by_id);
        ScheduleMapper::bind(query, dto);
        query.exec();
        query.next();
        return ScheduleMapper::toSchedule(query);
    }

    std::optional<Schedule> ScheduleDao::doGetById(int id) const
    {
        QSqlQuery query;
        query.prepare(sun::persistence::schedule::get_by_id);
        query.bindValue(":id", id);
        query.exec();
        if (query.next())
        {
            return ScheduleMapper::toSchedule(query);
        }
        return std::nullopt;
    }

    void ScheduleDao::doDeleteById(int id) const
    {
        QSqlQuery query;
        query.prepare(sun::persistence::schedule::delete_by_id);
        query.bindValue(":id", id);
        query.exec();
    }

    QList<Schedule> ScheduleDao::doGetAll() const
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

    void ScheduleDao::doAddApplicationList(int scheduleId, int listId) const
    {
        QSqlQuery query;
        query.prepare(sun::persistence::schedule::add_application_list);
        query.bindValue(":schedule_id", scheduleId);
        query.bindValue(":application_list_id", listId);
        query.exec();
    }

    void ScheduleDao::doRemoveApplicationList(int scheduleId, int listId) const
    {
        QSqlQuery query;
        query.prepare(sun::persistence::schedule::remove_application_list);
        query.bindValue(":schedule_id", scheduleId);
        query.bindValue(":application_list_id", listId);
        query.exec();
    }

    void ScheduleDao::doRemoveAllApplicationLists(int scheduleId) const
    {
        QSqlQuery query;
        query.prepare(sun::persistence::schedule::remove_all_application_lists);
        query.bindValue(":schedule_id", scheduleId);
        query.exec();
    }

    QList<ApplicationList> ScheduleDao::doGetAllApplicationLists(int scheduleId) const
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

    QList<Schedule> ScheduleDao::doGetAllByApplicationList(int listId) const
    {
        QSqlQuery query;
        query.prepare(sun::persistence::schedule::get_all_by_application_list);
        query.bindValue(":application_list_id", listId);
        query.exec();
        QList<Schedule> result;
        while (query.next())
        {
            result.append(ScheduleMapper::toSchedule(query));
        }
        return result;
    }
} // sun::persistence