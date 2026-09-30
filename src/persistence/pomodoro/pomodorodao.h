#pragma once

#include "pomodoro/pomodoro.h"
#include "applicationlist/applicationlist.h"

#include <QList>

namespace sun::persistence
{
    class PomodoroDao
    {
    public:
        Pomodoro create(const Pomodoro& pomodoro);
        Pomodoro updateById(int id, const Pomodoro& pomodoro);
        Pomodoro getById(int id);
        
        QList<Pomodoro> getAll();

        void deleteById(int id);
        
        void addApplicationList(int pomodoroId, int listId);
        void removeApplicationList(int pomodoroId, int listId);
        void removeAllAplicationLists(int pomodoroId);

        QList<ApplicationList> getApplicationLists(int pomodoroId);
    };
} // sun::persistence