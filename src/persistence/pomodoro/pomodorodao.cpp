#include "pomodoro/pomodorodao.h"
#include "pomodoro/pomodorosql.h"
#include "pomodoro/pomodoromapper.h"

#include "applicationlist/applicationlistmapper.h"

#include <QSqlQuery>

namespace sun::persistence
{
    Pomodoro PomodoroDao::create(const CreatePomodoroDto& dto)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::pomodoro::create);
        PomodoroMapper::bind(query, dto);
        query.exec();
        return PomodoroMapper::toPomodoro(query);
    }

    Pomodoro PomodoroDao::updateById(const UpdatePomodoroDto& dto)
    {
        QSqlQuery query;
        query.prepare(sun::persistence::pomodoro::update_by_id);
        PomodoroMapper::bind(query, dto);
        query.exec();
        return PomodoroMapper::toPomodoro(query);
    }

    Pomodoro PomodoroDao::getById(int id)
    {
        QSqlQuery query;
        query.bindValue(":id", id);
        query.exec();
        return PomodoroMapper::toPomodoro(query);
    }

    QList<Pomodoro> PomodoroDao::getAll()
    {
        QSqlQuery query;
        query.exec(sun::persistence::pomodoro::get_all);
        QList<Pomodoro> result;
        while (query.next())
        {
            result.append(PomodoroMapper::toPomodoro(query));
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
            result.append(ApplicationListMapper::toApplicationList(query));
        }
        return result;
    }

} // sun::persistence