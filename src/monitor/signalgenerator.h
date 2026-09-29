#pragma once

#include <QObject>
#include <QString>

struct ProcessInfo
{
    QString name;
};

class SignalGenerator : public QObject
{
    Q_OBJECT

public:
    SignalGenerator(QObject *parent = nullptr) : QObject(parent) {}

    signals:
        void usageStarted(const ProcessInfo proc);

        void usageEnded(const ProcessInfo proc);
};
