#pragma once

namespace sun::persistence::schema
{
    inline const auto create_application_table = 
        "CREATE TABLE application ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "process_name TEXT NOT NULL )";
}