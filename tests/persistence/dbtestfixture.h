#pragma once

#include "db/dbconnection.h"
#include "db/schema.h"

#include <QSqlQuery>

namespace sun::persistence::test
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

    inline DbTestFixture::DbTestFixture()
        : connection({"QSQLITE", ":memory:"})
    {
        createSchema();   
    }

    inline void DbTestFixture::createSchema()
    {
        QSqlQuery query;
        query.exec(schema::create_application_table);
        query.exec(schema::create_activity_table);
        query.exec(schema::create_application_list_table);
        query.exec(schema::create_application_list_application_table);
        query.exec(schema::create_schedule_table);
        query.exec(schema::create_schedule_application_list_table);
        query.exec(schema::create_pomodoro_table);
        query.exec(schema::create_pomodoro_application_list_table);
        query.exec(schema::enable_foreign_key_constrains);
    }
} // sun::persistence::test