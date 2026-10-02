#pragma once

#include "pomodoro/pomodoro.h"
#include "applicationlist/applicationlist.h"

#include <QList>

namespace sun::persistence
{
    class IPomodoroDao
    {
    public:
        Pomodoro create(const CreatePomodoroDto& dto) const;
        Pomodoro updateById(const UpdatePomodoroDto& dto) const;
        Pomodoro getById(int id) const;

        QList<Pomodoro> getAll() const;

        void deleteById(int id) const;
        
        void addApplicationList(int pomodoroId, int listId) const;
        void removeApplicationList(int pomodoroId, int listId) const;
        void removeAllAplicationLists(int pomodoroId) const;

        QList<ApplicationList> getApplicationLists(int pomodoroId) const;

    private:
        virtual Pomodoro doCreate(const CreatePomodoroDto& dto) const = 0;
        virtual Pomodoro doUpdateById(const UpdatePomodoroDto& dto) const = 0;
        virtual Pomodoro doGetById(int id) const = 0;

        virtual QList<Pomodoro> doGetAll() const = 0;

        virtual void doDeleteById(int id) const = 0;
        
        virtual void doAddApplicationList(int pomodoroId, int listId) const = 0;
        virtual void doRemoveApplicationList(int pomodoroId, int listId) const = 0;
        virtual void doRemoveAllAplicationLists(int pomodoroId) const = 0;

        virtual QList<ApplicationList> doGetApplicationLists(int pomodoroId) const = 0;
    };

    inline Pomodoro IPomodoroDao::create(const CreatePomodoroDto& dto) const
    {  
        return doCreate(dto);
    }

    inline Pomodoro IPomodoroDao::updateById(const UpdatePomodoroDto &dto) const
    {
        return doUpdateById(dto);
    }

    inline Pomodoro IPomodoroDao::getById(int id) const
    {
        return doGetById(id);
    }

    inline QList<Pomodoro> IPomodoroDao::getAll() const
    {
        return doGetAll();
    }

    inline void IPomodoroDao::deleteById(int id) const
    {
        return doDeleteById(id);
    }

    inline void IPomodoroDao::addApplicationList(int pomodoroId, int listId) const
    {
        return doAddApplicationList(pomodoroId, listId);
    }

    inline void IPomodoroDao::removeApplicationList(int pomodoroId, int listId) const
    {
        doRemoveApplicationList(pomodoroId, listId);
    }

    inline void IPomodoroDao::removeAllAplicationLists(int pomodoroId) const
    {
        doRemoveAllAplicationLists(pomodoroId);
    }

    inline QList<ApplicationList> IPomodoroDao::getApplicationLists(int pomodoroId) const
    {
        return doGetApplicationLists(pomodoroId);
    }

} // sun::persistence