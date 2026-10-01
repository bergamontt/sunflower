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
            query.value("process_name").toString()
        };
    }

    inline void ApplicationMapper::bind(QSqlQuery& query, const CreateApplicationDto& dto)
    {
        query.bindValue(":name", dto.name);
        query.bindValue(":process_name", dto.processName);
    }

    inline void ApplicationMapper::bind(QSqlQuery& query, const UpdateApplicationDto& dto)
    {
        query.bindValue(":name", dto.id);
        query.bindValue(":name", dto.name);
        query.bindValue(":process_name", dto.processName);
    }
} // sun::persistence