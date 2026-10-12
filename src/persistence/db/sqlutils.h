#pragma once

#include <QVariant>
#include <QMetaType>

#include <optional>

namespace sun::persistence 
{
    template<typename T>
    QVariant toVariant(const std::optional<T>& optional)
    {
        if (optional.has_value())
        {
            return QVariant::fromValue(*optional);
        }
        return QVariant();
    }

    template<typename T>
    std::optional<T> fromVariant(const QVariant& variant)
    {
        if (variant.isNull() || !variant.isValid())
        {
            return std::nullopt;
        }
        return variant.value<T>();
    }
}