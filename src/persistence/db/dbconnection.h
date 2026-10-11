#pragma once

#include <QString>
#include <QSqlDatabase>

namespace sun::persistence
{
    struct DbConnectionConfig
    {
        QString driverType;
        QString databaseName;
    };

    class DbConnection
    {
    public:
        DbConnection(const DbConnectionConfig& config);
        ~DbConnection();

        DbConnection(const DbConnection&) = delete;
        DbConnection& operator=(const DbConnection&) = delete;
    };
} // namespace sun::persistence