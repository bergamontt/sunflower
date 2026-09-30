#pragma once

#include "application/application.h"

#include <QSqlQuery>

namespace sun::persistence
{
    struct ApplicationMapper
    {
        static Application toApplication(const QSqlQuery& query);
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
} // sun::persistence