#pragma once

namespace sun::persistence::schedule
{
    inline const auto create =
        "INSERT INTO schedule (id, name, schedule_type, starts_at, ends_at, daily_limit, repeat_at, lock_type, lock_hash, unlock_after)"
        "VALUES (:id, :schedule_type, :starts_at, :ends_at, :daily_limit, :repeat_at, :lock_type, :lock_hash, :unlock_after)";

    inline const auto update_by_id =
        "UPDATE schedule"
        "SET name = :name"
        "schedule_type = :schedule_type"
        "starts_at = :starts_at"
        "ends_at = :ends_at"
        "daily_limit = :daily_limit"
        "repeat_at = :repeat_at"
        "lock_type = :lock_type"
        "lock_hash = :lock_hash"
        "unlock_after = :unlock_after"
        "WHERE id = :id";
    
    inline const auto delete_by_id = 
        "DELETE FROM schedule"
        "WHERE id = :id";
    
    inline const auto get_by_id = 
        "SELECT * FROM schedule"
        "WHERE id = :id";
    
    inline const auto get_all = 
        "SELECT * FROM schedule";
    
    inline const auto add_application_list =
        "INSERT INTO schedule_application_list (schedule_id, application_list_id)"
        "VALUES (:schedule_id, :applciation_list_id)";
    
    inline const auto remove_application_list =
        "DELETE FROM schedule_application_list"
        "WHERE schedule_id = :schedule_id"
        "AND application_list_id = :application_list_id";
    
    inline const auto remove_application_lists = 
        "DELETE FROM schedule_application_list"
        "WHERE schedule_id = :schedule_id";
} // sun::persistence::schedule