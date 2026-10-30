#pragma once

#include <QString>

namespace sun::core
{
    class IPasswordService
    {
    public:
        QString hash(const QString& password) const;
        bool matchPasswords(const QString& password, const QString& repeatPassword) const;
    private:
        virtual QString doHash(const QString& password) const = 0;
        virtual bool doMatchPasswords(const QString& password, const QString& repeatPassword) const = 0;
    };

    inline QString IPasswordService::hash(const QString& password) const
    {
        return doHash(password);
    }

    inline bool IPasswordService::matchPasswords(const QString& password, const QString& repeatPassword) const
    {
        return doMatchPasswords(password, repeatPassword);
    }
}