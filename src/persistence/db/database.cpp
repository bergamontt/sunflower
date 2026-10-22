#include "db/database.h"
#include "db/schema.h"

#include <QSqlQuery>
#include <QFile>
#include <QFileInfo>
#include <QDir>

namespace sun::persistence
{
    Database::Database(const QString &path)
        : path (path)
        , connection({"QSQLITE", path})
    {
        if (!QFile::exists(path))
        {
            createSchema();
        }
    }

    void sun::persistence::Database::createSchema()
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
}