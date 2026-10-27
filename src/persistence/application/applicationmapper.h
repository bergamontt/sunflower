#pragma once

#include "application/application.h"

#include <QSqlQuery>

namespace sun::persistence
{
    struct ApplicationMapper
    {
        static Application toApplication(const QSqlQuery& query);
        static void bind(QSqlQuery& query, const CreateApplicationDto& dto);
        static void bind(QSqlQuery& query, const UpdateApplicationDto& dto);
    };

    inline Application ApplicationMapper::toApplication(const QSqlQuery& query)
    {
        return 
        {
            query.value("id").toInt(),
            query.value("name").toString(),
            query.value("process_name").toString(),
            query.value("icon").toString(),
            query.value("source").toString()
        };
    }

    inline void ApplicationMapper::bind(QSqlQuery& query, const CreateApplicationDto& dto)
    {
        query.bindValue(":name", dto.name);
        query.bindValue(":process_name", dto.processName);
        query.bindValue(":icon", dto.icon);
        query.bindValue(":source", dto.source);
    }

    inline void ApplicationMapper::bind(QSqlQuery& query, const UpdateApplicationDto& dto)
    {
        query.bindValue(":id", dto.id);
        query.bindValue(":name", dto.name);
        query.bindValue(":process_name", dto.processName);
        query.bindValue(":icon", dto.icon);
        query.bindValue(":source", dto.source);
    }
} // sun::persistence