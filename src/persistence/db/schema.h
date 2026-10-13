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

    inline const auto create_application_list_table =
        "CREATE TABLE application_list ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT) ";
    
    inline const auto create_application_list_application_table =
        "CREATE TABLE application_list_application ( "
        "application_list_id INTEGER NOT NULL, "
        "application_id INTEGER NOT NULL, "
        "PRIMARY KEY (application_list_id, application_id)) ";

    inline const auto create_schedule_table =
        "CREATE TABLE schedule ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "type TEXT NOT NULL, "
        "lock_type TEXT NOT NULL, "
        "repeat_at INTEGER NOT NULL, "
        "starts_at TEXT, "
        "ends_at TEXT, "
        "daily_limit INTEGER, "
        "lock_hash TEXT, "
        "unlock_after INTEGER, "
        "unlock_requested_at TEXT) ";

    inline const auto create_schedule_application_list_table =
        "CREATE TABLE schedule_application_list ("
        "schedule_id INTEGER NOT NULL, "
        "application_list_id INTEGER NOT NULL, "
        "PRIMARY KEY(schedule_id, application_list_id))";

    inline const auto create_pomodoro_table =
        "CREATE TABLE pomodoro ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "work_duration INTEGER NOT NULL, "
        "break_duration INTEGER NOT NULL, "
        "ends_at TEXT NOT NULL, "
        "state TEXT NOT NULL) ";

    inline const auto create_pomodoro_application_list_table =
        "CREATE TABLE pomodoro_application_list ("
        "pomodoro_id INTEGER NOT NULL, "
        "application_list_id INTEGER NOT NULL, "
        "PRIMARY KEY(pomodoro_id, application_list_id))";
} // sun::persistence::schema