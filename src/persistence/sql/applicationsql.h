#pragma once

namespace sun::persistence::application
{
    inline const auto create =
        "INSERT application (is, name, process_name)"
        "VALUES (:id, :name, :process_name)";
    
    inline const auto update_by_id =
        "UPDATE application"
        "SET name = :name"
        "process_name = :process_name"
        "WHERE id = :id";
} // sun::persistence::application