#pragma once

#include "application/applicationdao.h"

#include <QList>

namespace sun::core
{
    class IApplicationService
    {
    public:
        persistence::Application create(const persistence::CreateApplicationDto& dto) const;
        QList<persistence::Application> create(const QList<persistence::CreateApplicationDto>& dtos) const;
        std::optional<persistence::Application> getById(int id) const;
        QList<persistence::Application> getAll() const;
        persistence::Application updateById(const persistence::UpdateApplicationDto& dto) const;
        void deleteById(int id) const;
    private:
        virtual persistence::Application doCreate(const persistence::CreateApplicationDto& dto) const = 0;
        virtual QList<persistence::Application> doCreate(const QList<persistence::CreateApplicationDto>& dtos) const = 0;
        virtual std::optional<persistence::Application> doGetById(int id) const = 0;
        virtual QList<persistence::Application> doGetAll() const = 0;
        virtual persistence::Application doUpdateById(const persistence::UpdateApplicationDto& dto) const = 0;
        virtual void doDeleteById(int id) const = 0;
    };

    inline persistence::Application IApplicationService::create(const persistence::CreateApplicationDto& dto) const
    {
        return doCreate(dto);
    }

    inline QList<persistence::Application> IApplicationService::create(const QList<persistence::CreateApplicationDto>& dtos) const
    {
        return doCreate(dtos);
    }

    inline std::optional<persistence::Application> IApplicationService::getById(int id) const
    {
        return doGetById(id);
    }

    inline QList<persistence::Application> IApplicationService::getAll() const
    {
        return doGetAll();
    }

    inline persistence::Application IApplicationService::updateById(const persistence::UpdateApplicationDto& dto) const
    {
        return doUpdateById(dto);
    }

    inline void IApplicationService::deleteById(int id) const
    {
        doDeleteById(id);
    }
}
