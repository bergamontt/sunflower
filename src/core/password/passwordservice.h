#pragma once

#include "password/ipasswordservice.h"

namespace sun::core
{
    class PasswordService : public IPasswordService
    {
    private:
        QString doHash(const QString& password) const override;
        bool doMatchPasswords(const QString &password, const QString& repeatPassword) const override;
    };
} // namespace sun::core