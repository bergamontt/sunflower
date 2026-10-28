#pragma once

namespace sun::persistence::application
{
    inline const auto create =
        "INSERT INTO application (name, process_name, icon, source) "
        "VALUES (:name, :process_name, :icon, :source) "
        "ON CONFLICT(source) DO UPDATE SET "
        "name = excluded.name, "
        "process_name = excluded.process_name, "
        "icon = excluded.icon "
        "RETURNING id, name, process_name, icon, source";
    
    inline const auto update_by_id =
        "UPDATE application "
        "SET name = :name, "
        "process_name = :process_name, "
        "icon = :icon, "
        "source = :source "
        "WHERE id = :id "
        "RETURNING id, name, process_name, icon, source ";
    
    inline const auto get_by_id =
        "SELECT * FROM application "
        "WHERE id = :id";

    inline const auto get_all =
        "SELECT * FROM application";
    
    inline const auto delete_by_id =
        "DELETE FROM application "
        "WHERE id = :id";
} // sun::persistence::application