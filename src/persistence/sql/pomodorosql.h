#pragma once

namespace std::persistence::pomodoro
{
    inline const auto create =
        "INSERT INTO pomodoro (id, work_duration, break_duration, ends_at)"
        "VALUES (:id, :work_duration, :break_duration, :ends_at)";
    
    inline const auto update_by_id =
        "UPDATE pomodoro"
        "SET work_duration = :work_duration"
        "break_duration = :break_duration"
        "ends_at = :ends_at"
        "WHERE id = :id";
    
    inline const auto delete_by_id =
        "DELETE FROM pomodoro"
        "WHERE id = :id";
    
    inline const auto get_by_id =
        "SELECT * FROM pomodoro"
        "WHERE id = :id";
    
    inline const auto get_all = 
        "SELECT * FROM pomodoro";
    
    inline const auto add_application_list =
        "INSERT INTO pomodoro_application_list (pomodoro_id, application_list_id)"
        "VALUES (:pomodoro_id, :application_list_id)";
    
    inline const auto remove_application_list =
        "DELETE FROM pomodoro_application_list"
        "WHERE pomodoro_id = :pomodoro_id"
        "application_list_id = :application_list_id";
    
    inline const auto remove_all_application_lists = 
        "DELETE FROM pomodoro_application_list"
        "WHERE pomodoro_id = :pomodoro_id";
} // std::persistence::pomodoro