#pragma once

namespace sun::persistence::activity
{
    inline const auto create = 
        "INSERT INTO activity (id, day_id, application_id, started_at, ended_at)"
        "VALUES (:id, :day_id, :application_id, :started_at, :ended_at);";
    
    inline const auto update_by_id =
        "UPDATE activity"
        "SET ended_at = :ended_at"
        "WHERE id = :id";
    
    inline const auto get_by_id =
        "SELECT * FROM activity"
        "WHERE id = :id";
} // sun::persistence::activity