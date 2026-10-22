#pragma once

#include "db/dbconnection.h"

#include <QString>

namespace sun::persistence
{
    class Database
    {
    public:
        Database(const QString& path);
    private:
        QString path;
        DbConnection connection;
    private: 
        void createSchema();
    };
}