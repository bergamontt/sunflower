#pragma once

namespace sun::persistence::schedule
{
    inline const auto create =
        "INSERT INTO schedule (name, type, starts_at, ends_at, daily_limit, repeat_at)"
        "VALUES (:name, :type, :starts_at, :ends_at, :daily_limit, :repeat_at) "
        "RETURNING id, name, type, starts_at, ends_at, daily_limit, repeat_at";

    inline const auto update_by_id =
        "UPDATE schedule "
        "SET name = :name, "
        "type = :type, "
        "starts_at = :starts_at, "
        "ends_at = :ends_at, "
        "daily_limit = :daily_limit, "
        "repeat_at = :repeat_at "
        "WHERE id = :id "
        "RETURNING id, name, type, starts_at, ends_at, daily_limit, repeat_at";
    
    inline const auto delete_by_id = 
        "DELETE FROM schedule "
        "WHERE id = :id";
    
    inline const auto get_by_id = 
        "SELECT * FROM schedule "
        "WHERE id = :id";
    
    inline const auto get_all = 
        "SELECT * FROM schedule";
    
    inline const auto add_application_list =
        "INSERT INTO schedule_application_list (schedule_id, application_list_id) "
        "VALUES (:schedule_id, :application_list_id)";
    
    inline const auto remove_application_list =
        "DELETE FROM schedule_application_list "
        "WHERE schedule_id = :schedule_id "
        "AND application_list_id = :application_list_id";
    
    inline const auto remove_all_application_lists = 
        "DELETE FROM schedule_application_list "
        "WHERE schedule_id = :schedule_id";
    
    inline const auto get_all_application_lists = 
        "SELECT * FROM application_list "
        "WHERE id IN ( "
        "SELECT application_list_id FROM schedule_application_list "
        "WHERE schedule_id = :schedule_id)";

    inline const auto get_all_by_application_list =
        "SELECT * FROM schedule "
        "WHERE id IN ( "
        "SELECT schedule_id FROM schedule_application_list "
        "WHERE application_list_id = :application_list_id)";
} // sun::persistence::schedule