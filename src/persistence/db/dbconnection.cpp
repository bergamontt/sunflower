#include "db/dbconnection.h"

namespace sun::persistence
{
    DbConnection::DbConnection(const DbConnectionConfig& config)
    {
        QSqlDatabase db;
        if (QSqlDatabase::contains(QSqlDatabase::defaultConnection))
        {
            db = QSqlDatabase::database(config.driverType);
        }
        else
        {
            db = QSqlDatabase::addDatabase(config.driverType);
        }
        if (!db.isOpen())
        {
            db.setDatabaseName(config.databaseName);
            db.open();
        }
    }

    DbConnection::~DbConnection()
    {
        if (QSqlDatabase::database().isOpen())
            QSqlDatabase::database().close();
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    }
} // namespace sun::persistence