#pragma once

#include "pomodoro/ipomodorodao.h"

namespace sun::persistence
{
    class PomodoroDao : public IPomodoroDao
    {
    private:
        Pomodoro doCreate(const CreatePomodoroDto& dto) const override;
        Pomodoro doUpdateById(const UpdatePomodoroDto& dto) const override;
        Pomodoro doGetById(int id) const override;

        QList<Pomodoro> doGetAll() const override;

        void doDeleteById(int id) const override;
        
        void doAddApplicationList(int pomodoroId, int listId) const override;
        void doRemoveApplicationList(int pomodoroId, int listId) const override;
        void doRemoveAllAplicationLists(int pomodoroId) const override;

        QList<ApplicationList> doGetApplicationLists(int pomodoroId) const override;
    };
}