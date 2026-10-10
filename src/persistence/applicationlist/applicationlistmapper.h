#pragma once

#include "applicationlist/applicationlist.h"

#include "utils.h"

#include <QSqlQuery>

namespace sun::persistence
{
    struct ApplicationListMapper
    {
        static ApplicationList toApplicationList(const QSqlQuery& query);
        static void bind(QSqlQuery& query, const CreateApplicationListDto& dto);
        static void bind(QSqlQuery& query, const UpdateApplicationListDto& dto);
    };

    inline ApplicationList ApplicationListMapper::toApplicationList(const QSqlQuery& query)
    {
        return
        {
            query.value("id").toInt(),
            query.value("name").toString()
        };
    }
    
    inline void ApplicationListMapper::bind(QSqlQuery& query, const CreateApplicationListDto& dto)
    {
        query.bindValue(":name", toVariant(dto.name));
    }

    inline void ApplicationListMapper::bind(QSqlQuery& query, const UpdateApplicationListDto& dto)
    {
        query.bindValue(":id", dto.id);
        query.bindValue(":name", toVariant(dto.name));
    }
} // sun::persistence