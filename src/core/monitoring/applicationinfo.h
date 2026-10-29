#pragma once

#include "application/application.h"
#include "activity/activity.h"
#include "applicationlist/applicationlistdao.h"
#include "activity/activitydao.h"
#include "schedule/scheduledao.h"
#include "monitor.h"

#include <chrono>
#include <utility>
#include <schedule/schedule.h>
#include <QTimer>

namespace sun::core
{
    class ApplicationInfoDto
    {
    public:
        explicit ApplicationInfoDto(
            int id,
            QString name,
            QIcon icon,
            const std::chrono::seconds activity,
            const std::optional<std::chrono::seconds> left,
            const std::optional<persistence::Schedule::Type> scheduleType,
            QList<persistence::Activity> activityHistory
        )
            : id(id), name(std::move(name)), icon(std::move(icon)), todayActivity(activity),
              timeLeft(left), scheduleType(scheduleType), activityHistory(activityHistory)
        {
        }

        [[nodiscard]] int getId() const { return id; };

        [[nodiscard]] QString getName() const { return name; }

        [[nodiscard]] QIcon getIcon() const { return icon; }

        [[nodiscard]] std::chrono::seconds getTodayActivity() const { return todayActivity; }

        [[nodiscard]] std::optional<std::chrono::seconds> getTimeLeft() const { return timeLeft; }

        [[nodiscard]] std::optional<persistence::Schedule::Type> getScheduleType() const { return scheduleType; }

        [[nodiscard]] const QList<persistence::Activity>& getActivityHistory() const { return activityHistory; }

    private:
        int id;
        QString name;
        QIcon icon;

        std::chrono::seconds todayActivity;
        std::optional<std::chrono::seconds> timeLeft;
        std::optional<persistence::Schedule::Type> scheduleType;
        QList<persistence::Activity> activityHistory;
    };

    class ApplicationInfo
    {
    public:
        explicit ApplicationInfo(persistence::Application app);

        [[nodiscard]] const persistence::Application& getApplication() const;

        void setWindow(const monitor::Window& window);

        const std::optional<monitor::Window>& getWindow() const;

        [[nodiscard]] bool isActive() const;

        void setActive();

        void setInactive();

        [[nodiscard]] ApplicationInfoDto constructDto();

    private:
        std::chrono::seconds getTodayActivity();

        void updateCurrentActivityEnd();

        std::shared_ptr<persistence::IScheduleDao> scheduleDaoPtr;
        std::shared_ptr<persistence::IApplicationListDao> applicationListDaoPtr;
        std::shared_ptr<persistence::IActivityDao> activityDaoPtr;

        persistence::Application application;
        std::optional<monitor::Window> window;
        QList<persistence::Activity> priorActivities;
        std::optional<persistence::Activity> currentActivity;
        QList<persistence::Schedule> schedules;
        std::map<int, std::shared_ptr<QTimer>> timers;

        std::shared_ptr<QTimer> activitySaveTimer;
    };
}
