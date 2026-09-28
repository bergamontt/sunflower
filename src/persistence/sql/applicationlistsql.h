#pragma once

namespace sun::persistence::application_list
{
    inline const auto create = 
        "INSERT INTO application_list (id, name)"
        "VALUES (:id, :name)";

    inline const auto get_by_id =
        "SELECT * FROM application_list al"
        "WHERE al.id = :id";
    
    inline const auto get_all =
        "SELECT * FROM application_list";

    inline const auto add_application =
        "INSERT INTO application_list_application (application_list_id, application_id)"
        "VALUES (:application_list_id, :application_id)";

    inline const auto remove_application =
        "DELETE FROM application_list_application" 
        "WHERE application_list_id = :application_list_id"
        "application_id = :application_id";
    
    inline const auto remove_all_applications = 
        "DELETE FROM application_list_application"
        "WHERE application_list_id = :application_list_id";
    
    inline const auto get_all_applications =
        "SELECT * FROM application_list_application"
        "WHERE application_list = :application_list";
} // sun::persistence::application_list