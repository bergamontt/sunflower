#pragma once

#include <QObject>
#include <QString>

struct ProcessInfo
{
    QString name;
};

class Monitor : public QObject
{
    Q_OBJECT

public:
    Monitor(QObject *parent = nullptr) : QObject(parent) {}

    signals:
        void usageStarted(const ProcessInfo proc);

        void usageEnded(const ProcessInfo proc);
};
