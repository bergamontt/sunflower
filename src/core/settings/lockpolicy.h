#pragma once

#include <QString>
#include <QVariant>

namespace sun::core
{
    enum class LockType
    {
        None,
        Password,
        Delay
    };

    class LockPolicy
    {
    public:
        static LockPolicy none();
        static LockPolicy password(const QString& hash);
        static LockPolicy delay(int seconds);
    public:
        LockType lockType() const;
        QString hash() const;
        int delay() const;
    private:
        LockPolicy(LockType type, QVariant value);
    private:
        LockType type;
        QVariant value;
    };
} // sun::core