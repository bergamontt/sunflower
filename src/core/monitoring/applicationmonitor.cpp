#include "applicationmonitor.h"

#include "applicationlist/applicationlistdao.h"
#include "activity/activitydao.h"
#include "schedule/scheduledao.h"
#include "monitorfactory.h"

namespace sun::core
{
    using namespace std;
    using namespace persistence;
    using namespace monitor;
    using namespace std::chrono;

    ApplicationMonitor::ApplicationMonitor(QObject* parent) :
        QObject(parent),
        monitorPtr(sun::monitor::createMonitor()),
        applicationDaoPtr(make_unique<ApplicationDao>()),
        applicationListDaoPtr(make_unique<ApplicationListDao>()),
        activityDaoPtr(make_unique<ActivityDao>()),
        scheduleDaoPtr(make_unique<ScheduleDao>()) {}

    void ApplicationMonitor::discoverApplications()
    {
        for (const auto& app : applicationDaoPtr->getAll())
        {
            auto appInfo = std::make_shared<ApplicationInfo>(app);
            auto dto = appInfo->constructDto();

            applications.append(std::move(appInfo));
            applicationDiscovered(dto);
        }

        QObject::connect(
            monitorPtr.get(),
            &sun::monitor::Monitor::usageStarted,
            this,
            &sun::core::ApplicationMonitor::handleUsageStarted
        );

        QObject::connect(
            monitorPtr.get(),
            &sun::monitor::Monitor::usageEnded,
            this,
            &sun::core::ApplicationMonitor::handleUsageEnded
        );

        monitorPtr->startMonitoring();
    }

    static bool represents(const ApplicationInfo& app, const Window& window)
    {
        return window.getName().contains(app.getApplication().name, Qt::CaseInsensitive);
    }

    void ApplicationMonitor::handleUsageStarted(Window window)
    {
        if (window.getName().isEmpty())
            return;
        for (auto& appInfo : applications)
        {
            if (window == appInfo->getWindow() || represents(*appInfo, window))
            {
                appInfo->setWindow(window);
                if (!appInfo->isActive())
                    appInfo->setActive();
                usageStarted(appInfo->constructDto());
                return;
            }
        }
    }

    void ApplicationMonitor::handleUsageEnded(Window window)
    {
        for (auto& appInfo : applications)
        {
            if (window == appInfo->getWindow())
            {
                appInfo->setInactive();
                usageEnded(appInfo->constructDto());
            }
        }
    }
}
