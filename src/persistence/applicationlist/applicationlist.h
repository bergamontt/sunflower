#pragma once

#include <QString>

#include <optional>

namespace sun::persistence
{
    struct ApplicationList
    {
        int id;
        std::optional<QString> name;
    };

    struct CreateApplicationListDto
    {
        std::optional<QString> name;
    };

    struct UpdateApplicationListDto
    {
        int id;
        std::optional<QString> name;
    };

    inline bool operator==(const ApplicationList& a, const ApplicationList& b)
    {
        return a.id == b.id && a.name == b.name;
    }
} // sun::persistence