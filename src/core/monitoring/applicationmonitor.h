#pragma once

#include "application/applicationdao.h"
#include "applicationlist/applicationlistdao.h"
#include "activity/activitydao.h"
#include "schedule/scheduledao.h"

#include "monitor.h"
#include "window.h"
#include "applicationinfo.h"

#include <QTimer>

namespace sun::core
{
    class ApplicationMonitor : public QObject
    {
        Q_OBJECT

    public:
        explicit ApplicationMonitor(QObject* parent = nullptr);

    public slots:
        void handleUsageStarted(sun::monitor::Window window);

        void handleUsageEnded(sun::monitor::Window window);

    signals:
        void applicationDiscovered(sun::core::ApplicationInfoDto application);

        void usageStarted(sun::core::ApplicationInfoDto application);

        void usageEnded(sun::core::ApplicationInfoDto application);

    private:
        persistence::Application saveAsApplication(const monitor::Window& window) const;

        std::unique_ptr<persistence::IApplicationDao> applicationDaoPtr;
        std::unique_ptr<persistence::IApplicationListDao> applicationListDaoPtr;
        std::unique_ptr<persistence::IActivityDao> activityDaoPtr;
        std::unique_ptr<persistence::IScheduleDao> scheduleDaoPtr;

        QList<ApplicationInfo> applications;
    };
}
