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
    //  "FOREIGN KEY (application_id) REFERENCES applciation(id));";

    inline const auto create_application_list_table = 
        "CREATE TABLE application_list ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT) ";
    
    inline const auto create_application_list_application_table =
        "CREATE TABLE application_list_application ( "
        "application_list_id INTEGER NOT NULL, "
        "application_id INTEGER NOT NULL, "
        "PRIMARY KEY (application_list_id, application_id)) ";
}