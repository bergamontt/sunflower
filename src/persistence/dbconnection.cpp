#include "dbconnection.h"

namespace sun::persistence
{
    DbConnection::DbConnection(const DbConnectionConfig& config)
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(config.driverType);
        db.setDatabaseName(config.databaseName);
    }

    DbConnection::~DbConnection()
    {
        QSqlDatabase::database().close();
    }
} // namespace sun::persistence