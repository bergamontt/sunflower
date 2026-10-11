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
        return QVariant(QMetaType::fromType<T>());
    }
}