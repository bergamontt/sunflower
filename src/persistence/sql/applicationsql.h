#pragma once

namespace sun::persistence::application
{
    inline const auto create =
        "INSERT application (name, process_name) "
        "VALUES (:name, :process_name) "
        "RETURNING id, name, process_name";
    
    inline const auto update_by_id =
        "UPDATE application "
        "SET name = :name "
        "process_name = :process_name "
        "WHERE id = :id "
        "RETURNING id, name, process_name ";
    
    inline const auto get_by_id =
        "SELECT * FROM application "
        "WHERE id = :id";
    
    inline const auto delete_by_id =
        "DELETE FROM application "
        "WHERE id = :id";
} // sun::persistence::application