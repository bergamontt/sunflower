#pragma once

namespace sun::persistence::schema
{
    inline const auto create_application_table = 
        "CREATE TABLE application ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "process_name TEXT NOT NULL )";

    inline const auto create_activity_table =
        "CREATE TABLE activity ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "application_id INTEGER NOT NULL, "
        "started_at TEXT NOT NULL, "
        "ended_at TEXT) ";
        //"FOREIGN KEY (application_id) REFERENCES applciation(id));";
}