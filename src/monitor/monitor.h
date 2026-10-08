#pragma once

#include <QObject>
#include <QString>

namespace sun::monitor
{
    struct ProcessInfo
    {
        pid_t pid;
        QString name;
    };

    class Monitor : public QObject
    {
        Q_OBJECT

    public:
        explicit Monitor(QObject* parent = nullptr) : QObject(parent) {}

        ~Monitor() override = default;

        virtual void startMonitoring() = 0;

    signals:
        void usageStarted(const sun::monitor::ProcessInfo& proc);
        void usageEnded(const sun::monitor::ProcessInfo& proc);
    };
}