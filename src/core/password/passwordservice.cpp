#include "password/passwordservice.h"

#include <QCryptographicHash>

namespace sun::core
{
    QString PasswordService::hash(const QString &password) const
    {
        const QByteArray hashBytes = QCryptographicHash::hash(
            password.toUtf8(), 
            QCryptographicHash::Sha256
        );
        return QString::fromUtf8(hashBytes.toHex());
    }

    bool PasswordService::matchPasswords(const QString &password, const QString& repeatPassword) const
    {
        if (password.trimmed().isEmpty())
        {
            return false;
        }
        if (password != repeatPassword)
        {
            return false;
        }
        return true;
    }
}