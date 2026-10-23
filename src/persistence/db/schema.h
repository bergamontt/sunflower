#pragma once

namespace sun::persistence::schema
{
    inline const auto create_application_table = 
        "CREATE TABLE IF NOT EXISTS application ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "process_name TEXT NOT NULL )";

    inline const auto create_activity_table =
        "CREATE TABLE IF NOT EXISTS activity ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "application_id INTEGER NOT NULL REFERENCES application(id), "
        "started_at TEXT NOT NULL, "
        "ended_at TEXT) ";

    inline const auto create_application_list_table =
        "CREATE TABLE IF NOT EXISTS application_list ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT) ";
    
    inline const auto create_application_list_application_table =
        "CREATE TABLE IF NOT EXISTS application_list_application ( "
        "application_list_id INTEGER NOT NULL REFERENCES application_list(id), "
        "application_id INTEGER NOT NULL REFERENCES application(id), "
        "PRIMARY KEY (application_list_id, application_id)) ";

    inline const auto create_schedule_table =
        "CREATE TABLE IF NOT EXISTS schedule ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "type TEXT NOT NULL, "
        "is_active INTEGER NOT NULL, "
        "repeat_at INTEGER NOT NULL, "
        "starts_at TEXT, "
        "ends_at TEXT, "
        "daily_limit INTEGER) ";

    inline const auto create_schedule_application_list_table =
        "CREATE TABLE IF NOT EXISTS schedule_application_list ("
        "schedule_id INTEGER NOT NULL REFERENCES schedule(id), "
        "application_list_id INTEGER NOT NULL REFERENCES application_list(id), "
        "PRIMARY KEY(schedule_id, application_list_id))";

    inline const auto create_pomodoro_table =
        "CREATE TABLE IF NOT EXISTS pomodoro ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "work_duration INTEGER NOT NULL, "
        "break_duration INTEGER NOT NULL, "
        "ends_at TEXT NOT NULL, "
        "state TEXT NOT NULL) ";

    inline const auto create_pomodoro_application_list_table =
        "CREATE TABLE IF NOT EXISTS pomodoro_application_list ("
        "pomodoro_id INTEGER NOT NULL REFERENCES pomodoro(id), "
        "application_list_id INTEGER NOT NULL REFERENCES application_list(id), "
        "PRIMARY KEY(pomodoro_id, application_list_id))";

    inline const auto enable_foreign_key_constrains = 
        "PRAGMA foreign_keys = ON;";
} // sun::persistence::schema