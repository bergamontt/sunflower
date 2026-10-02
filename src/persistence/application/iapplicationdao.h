#pragma once

#include "application/application.h"

namespace sun::persistence 
{
    class IApplicationDao
    {
    public:    
        Application create(const CreateApplicationDto& dto) const;
        Application updateById(const UpdateApplicationDto& dto) const;
        Application getById(int id) const;
        void deleteById(int id) const;
    private:
        virtual Application doCreate(const CreateApplicationDto& dto) const = 0;
        virtual Application doUpdateById(const UpdateApplicationDto& dto) const = 0;
        virtual Application doGetById(int id) const = 0;
        virtual void doDeleteById(int id) const = 0;
    };

    inline Application IApplicationDao::create(const CreateApplicationDto &dto) const
    {
        return doCreate(dto);
    }

    inline Application IApplicationDao::updateById(const UpdateApplicationDto &dto) const
    {
        return doUpdateById(dto);
    }

    inline Application IApplicationDao::getById(int id) const
    {
        return doGetById(id);
    }

    inline void IApplicationDao::deleteById(int id) const
    {
        return doDeleteById(id);
    }
}