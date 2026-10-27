#pragma once

namespace sun::persistence::application
{
    inline const auto create =
        "INSERT INTO application (name, process_name, icon) "
        "VALUES (:name, :process_name, :icon) "
        "RETURNING id, name, process_name, icon";
    
    inline const auto update_by_id =
        "UPDATE application "
        "SET name = :name, "
        "process_name = :process_name, "
        "icon = :icon "
        "WHERE id = :id "
        "RETURNING id, name, process_name, icon ";
    
    inline const auto get_by_id =
        "SELECT * FROM application "
        "WHERE id = :id";

    inline const auto get_all =
        "SELECT * FROM application";
    
    inline const auto delete_by_id =
        "DELETE FROM application "
        "WHERE id = :id";
} // sun::persistence::application