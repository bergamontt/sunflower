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
} // sun::persistence