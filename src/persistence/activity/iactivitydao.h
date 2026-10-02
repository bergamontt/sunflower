#pragma once

#include "activity/activity.h"

#include <QDateTime>

namespace sun::persistence
{
    class IActivityDao
    {
    public:
        Activity create(const CreateActivityDto& dto) const;
        Activity updateById(const UpdateActivityDto& dto) const;
        Activity getById(int id) const;
        void deleteById(int id) const;
    private:
        virtual Activity doCreate(const CreateActivityDto& dto) const = 0;
        virtual Activity doUpdateGetById(const UpdateActivityDto& dto) const = 0;
        virtual Activity doGetById(int id) const = 0;
        virtual void doDeleteById(int id) const = 0;
    };

    inline Activity IActivityDao::create(const CreateActivityDto &dto) const
    {
        return doCreate(dto);
    }

    inline Activity IActivityDao::updateById(const UpdateActivityDto& dto) const
    {
        return doUpdateGetById(dto);
    }

    inline Activity IActivityDao::getById(int id) const
    {
        return doGetById(id);
    }

    inline void IActivityDao::deleteById(int id) const
    {
        return doDeleteById(id);
    }

} // sun::persistence
