#pragma once

#include "monitor.h"

#include <QObject>
#include <QTemporaryFile>

#include <memory>

namespace sun::monitor::wayland
{
    class KdeWaylandMonitor : public Monitor
    {
        Q_OBJECT
        Q_CLASSINFO("D-Bus Interface", "org.sun.monitor.KWinReceiver")
    public:
        explicit KdeWaylandMonitor(QObject* parent = nullptr);
        ~KdeWaylandMonitor() override;
    public:
        void startMonitoring() override;
    public slots:
        void onWindowOpened(const QString& windowId, const QString& name);
        void onWindowClosed(const QString& windowId, const QString& name);
    private:
        int scriptId = -1;
        std::unique_ptr<QTemporaryFile> script;
    };
} //sun::monitor::wayland