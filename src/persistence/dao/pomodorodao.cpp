#include "pomodorodao.h"

#include "../sql/pomodorosql.h"

#include <QSqlQuery>

namespace sun::persistence
{
    Pomodoro PomodoroDao::create(const Pomodoro& pomodoro)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::pomodoro::create);
        query.bindValue(":work_duration", pomodoro.workDuration);
        query.bindValue(":break_duration", pomodoro.breakDuration);
        query.bindValue(":ends_at", pomodoro.endsAt);
        query.bindValue(":state", pomodoro.state);
        query.exec();
        return 
        {
            query.value("id").toInt(),
            query.value("work_dauration").toInt(),
            query.value("break_duration").toInt(),
            query.value("ends_at").toDateTime(),
            toState(query.value("state").toString())
        };
    }

    Pomodoro PomodoroDao::updateById(int id, const Pomodoro &pomodoro)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::pomodoro::update_by_id);
        query.bindValue(":id", pomodoro.id);
        query.bindValue(":work_duration", pomodoro.workDuration);
        query.bindValue(":break_duration", pomodoro.breakDuration);
        query.bindValue(":ends_at", pomodoro.endsAt);
        query.bindValue(":state", pomodoro.state);
        query.exec();
        return 
        {
            query.value("id").toInt(),
            query.value("work_dauration").toInt(),
            query.value("break_duration").toInt(),
            query.value("ends_at").toDateTime(),
            toState(query.value("state").toString())
        };
    }

    Pomodoro PomodoroDao::getById(int id)
    {
        QSqlQuery query;
        query.bindValue(":id", id);
        query.exec();
        return
        {
            query.value("id").toInt(),
            query.value("work_dauration").toInt(),
            query.value("break_duration").toInt(),
            query.value("ends_at").toDateTime(),
            toState(query.value("state").toString())
        };
    }

    QList<Pomodoro> PomodoroDao::getAll()
    {
        QSqlQuery query;
        query.exec(sun::persistence::pomodoro::get_all);
        QList<Pomodoro> result;
        while (query.next())
        {
            result.append({
                query.value("id").toInt(),
                query.value("work_dartion").toInt(),
                query.value("break_duration").toInt(),
                query.value("ends_at").toDateTime(),
                toState(query.value("state").toString())
            });
        }
        return result;
    }

    void PomodoroDao::deleteById(int id)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::pomodoro::delete_by_id);
        query.bindValue(":id", id);
        query.exec();
    }

    void PomodoroDao::addApplicationList(int pomodoroId, int listId)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::pomodoro::add_application_list);
        query.bindValue(":pomodoro_id", pomodoroId);
        query.bindValue(":application_list_id", listId);
        query.exec();
    }

    void PomodoroDao::removeApplicationList(int pomodoroId, int listId)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::pomodoro::remove_application_list);
        query.bindValue(":pomodoro_id", pomodoroId);
        query.bindValue(":application_list_id", listId);
        query.exec();
    }

    void PomodoroDao::removeAllAplicationLists(int pomodoroId)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::pomodoro::remove_all_application_lists);
        query.bindValue(":pomodoro_id", pomodoroId);
        query.exec();
    }

    QList<ApplicationList> PomodoroDao::getApplicationLists(int pomodoroId)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::pomodoro::get_application_lists);
        query.bindValue(":pomodoro_id", pomodoroId);
        QList<ApplicationList> result;
        while (query.next())
        {
            result.append({
                query.value("id").toInt(),
                query.value("name").toString()
            });
        }
        return result;
    }

} // sun::persistence