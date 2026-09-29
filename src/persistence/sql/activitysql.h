#pragma once

namespace sun::persistence::activity
{
    inline const auto create = 
        "INSERT INTO activity (application_id, started_at, ended_at)"
        "VALUES (:application_id, :started_at, :ended_at) "
        "RETURNING id, application_id, started_at, ended_at";
    
    inline const auto update_ended_at =
        "UPDATE activity"
        "SET ended_at = :ended_at "
        "WHERE id = :id" 
        "RETURNING id, application_id, started_at, ended_at";
    
    inline const auto get_by_id =
        "SELECT * FROM activity "
        "WHERE id = :id";
    
    inline const auto delete_by_id =
        "DELETE FROM activity "
        "WHERE id = :id";
} // sun::persistence::activity