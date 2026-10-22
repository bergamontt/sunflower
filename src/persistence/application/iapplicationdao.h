#pragma once

#include "application/application.h"

namespace sun::persistence 
{
    class IApplicationDao
    {
    public:    
        Application create(const CreateApplicationDto& dto) const;
        Application updateById(const UpdateApplicationDto& dto) const;
        std::optional<Application> getById(int id) const;
        QList<Application> getAll() const;
        void deleteById(int id) const;
    private:
        virtual Application doCreate(const CreateApplicationDto& dto) const = 0;
        virtual Application doUpdateById(const UpdateApplicationDto& dto) const = 0;
        virtual std::optional<Application> doGetById(int id) const = 0;
        virtual QList<Application> doGetAll() const = 0;
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

    inline std::optional<Application> IApplicationDao::getById(int id) const
    {
        return doGetById(id);
    }

    inline QList<Application> IApplicationDao::getAll() const
    {
        return doGetAll();
    }

    inline void IApplicationDao::deleteById(int id) const
    {
        return doDeleteById(id);
    }
}