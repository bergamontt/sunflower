#include "applicationmonitor.h"

#include "applicationlist/applicationlistdao.h"
#include "activity/activitydao.h"
#include "schedule/scheduledao.h"

namespace sun::core
{
    using namespace std;
    using namespace persistence;
    using namespace monitor;
    using namespace std::chrono;

    ApplicationMonitor::ApplicationMonitor(QObject* parent) :
        QObject(parent),
        applicationDaoPtr(make_unique<ApplicationDao>()),
        applicationListDaoPtr(make_unique<ApplicationListDao>()),
        activityDaoPtr(make_unique<ActivityDao>()),
        scheduleDaoPtr(make_unique<ScheduleDao>()) {}

    void ApplicationMonitor::discoverApplications()
    {
        for (const auto& app : applicationDaoPtr->getAll())
        {
            auto appInfo = ApplicationInfo(app);
            applications.append(appInfo);
            applicationDiscovered(appInfo.constructDto());
        }
    }

    static bool represents(const ApplicationInfo& app, const Window& window)
    {
        return window.getName().contains(app.getApplication().name, Qt::CaseInsensitive);
    }
    
    Application ApplicationMonitor::saveAsApplication(const Window& window) const
    {
        auto app = applicationDaoPtr->create({window.getName(), window.getName()});
        return app;
    }

    void ApplicationMonitor::handleUsageStarted(Window window)
    {
        if (window.getName().isEmpty())
            return;
        for (auto& appInfo : applications)
        {
            if (window == appInfo.getWindow() || represents(appInfo, window))
            {
                appInfo.setWindow(window);
                if (!appInfo.isActive())
                    appInfo.setActive();
                usageStarted(appInfo.constructDto());
                return;
            }
        }

        auto appInfo = ApplicationInfo(saveAsApplication(window));
        applications.append(appInfo);
        applicationDiscovered(appInfo.constructDto());
        appInfo.setActive();
        usageStarted(appInfo.constructDto());
    }

    void ApplicationMonitor::handleUsageEnded(Window window)
    {
        for (auto& appInfo : applications)
        {
            if (window == appInfo.getWindow())
            {
                appInfo.setInactive();
                usageEnded(appInfo.constructDto());
            }
        }
    }
}
