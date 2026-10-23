#pragma once

#include <QString>

namespace sun::core
{
    class PasswordService
    {
    public:
        QString hash(const QString& password) const;
        bool matchPasswords(const QString &password, const QString& repeatPassword) const;
    };
} // namespace sun::core