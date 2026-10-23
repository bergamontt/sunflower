#pragma once

#include "activity/iactivitydao.h"

namespace sun::persistence
{
    class ActivityDao : public IActivityDao
    {  
    private:
        Activity doCreate(const CreateActivityDto& dto) const override;
        Activity doUpdateGetById(const UpdateActivityDto& dto) const override;
        std::optional<Activity> doGetById(int id) const override;
        QList<Activity> doGetAllByApplicationId(int id) const override;
        void doDeleteById(int id) const override;
    };
}