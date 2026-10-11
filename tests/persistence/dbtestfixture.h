#pragma once

#include "db/dbconnection.h"
#include "db/schema.h"

#include <QSqlQuery>
#include <QSqlError>

namespace sun::persistence::tests
{
    class DbTestFixture
    {
    public:
        DbTestFixture();
    private: 
        DbConnection connection;
    private:
        void createSchema();
    };

    DbTestFixture::DbTestFixture()
        : connection({"QSQLITE", ":memory:"})
    {
        createSchema();   
    }

    void DbTestFixture::createSchema()
    {
        QSqlQuery query;
        query.exec(schema::create_application_table);
    }
}