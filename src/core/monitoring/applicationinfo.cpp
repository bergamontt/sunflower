#include "applicationinfo.h"

#include <algorithm>
#include <limits>
#include <ranges>

namespace sun::core
{
    using namespace std;
    using namespace chrono;
    using namespace persistence;

    static Schedule::Day currentDayOfWeek()
    {
        const int dayNum = QDate::currentDate().dayOfWeek() - 1;
        return static_cast<Schedule::Day>(1 << dayNum);
    }

    static optional<seconds> timeLeft(const optional<Schedule>& schedule, const optional<seconds> currentActivity)
    {
        if (!currentActivity)
            return nullopt;

        if (!schedule || !(schedule->isActive) || !(schedule->repeatAt & currentDayOfWeek()))
            return nullopt;

        switch (schedule->type)
        {
        case Schedule::DailyLimit:
        {
            const auto limit = seconds(*schedule->dailyLimit);
            return max(seconds::zero(), duration_cast<seconds>(limit) - *currentActivity);
        }

        case Schedule::TimeWindow:
        {
            const QTime now = QTime::currentTime();
            const QTime startsAt = *schedule->startsAt;
            const QTime endsAt = *schedule->endsAt;
            const QTime midnight = QTime(23, 59, 59);

            if (startsAt <= now && now < endsAt)
                return seconds::zero();

            if (now < startsAt)
                return seconds(now.secsTo(startsAt));
            else
                return seconds(now.secsTo(midnight));
        }
        }

        return nullopt;
    }

    static QIcon loadApplicationIcon(const QString& name)
    {
        QIcon icon = QIcon::fromTheme(name);
        if (!icon.isNull())
            return icon;

        icon = QIcon(name);
        if (!icon.isNull())
            return icon;

        return QIcon();
    }

    ApplicationInfo::ApplicationInfo(persistence::Application app) :
        scheduleDaoPtr(make_shared<ScheduleDao>()),
        applicationListDaoPtr(make_shared<ApplicationListDao>()),
        activityDaoPtr(make_shared<ActivityDao>()),
        application(move(app))
    {
        QList<ApplicationList> appLists = applicationListDaoPtr->getAllByApplication(application.id);
        for (const auto& appList : appLists)
            schedules.append(scheduleDaoPtr->getAllByApplicationList(appList.id));
        QList<Activity> activities = activityDaoPtr->getAllByApplicationId(application.id);
        priorActivities = activities;
    }

    ApplicationInfoDto ApplicationInfo::constructDto()
    {
        optional<Schedule> minSchedule;
        optional<seconds> secondsLeft;
        const optional<seconds> todayActivity = getTodayActivity();
        for (const auto& schedule : schedules)
        {
            const auto left = timeLeft(schedule, todayActivity);
            if (!secondsLeft || (left && *left < *secondsLeft))
            {
                secondsLeft = left;
                minSchedule = schedule;
            }
        }

        auto activities = priorActivities;
        if (currentActivity) {
            activities.append(*currentActivity);
        }

        return ApplicationInfoDto(
            application.id,
            application.name,
            loadApplicationIcon(application.icon),
            todayActivity,
            secondsLeft,
            minSchedule ? make_optional(minSchedule->type) : nullopt,
            activities
        );
    }

    const Application& ApplicationInfo::getApplication() const
    {
        return application;
    }

    void ApplicationInfo::setWindow(const monitor::Window& w)
    {
        this->window = w;
    }

    const optional<monitor::Window>& ApplicationInfo::getWindow() const
    {
        return this->window;
    }

    std::optional<seconds> ApplicationInfo::getTodayActivity()
    {
        const auto now = QDateTime::currentDateTime();
        const auto midnight = QDateTime(QDate::currentDate(), QTime(0, 0));
        seconds total = seconds::zero();
        bool hasActivityToday = false;

        const auto addActivity = [&](const Activity& activity)
        {
            const auto start = max(activity.startedAt, midnight);
            const auto end = min(activity.endedAt.value_or(now), now);
            if (start < end)
            {
                total += seconds(start.secsTo(end));
                hasActivityToday = true;
            }
        };

        for (const auto& activity : priorActivities)
            addActivity(activity);

        if (currentActivity)
            addActivity(*currentActivity);

        if (!hasActivityToday)
            return nullopt;

        return total;
    }

    void ApplicationInfo::updateCurrentActivityEnd()
    {
        if (!currentActivity)
            return;
        const auto now = QDateTime::currentDateTime();
        currentActivity->endedAt = now;
        activityDaoPtr->updateById({ currentActivity->id, now });
    }

    bool ApplicationInfo::isActive() const
    {
        return currentActivity.has_value();
    }

    void ApplicationInfo::setActive()
    {
        if (isActive())
            return;

        auto activityToday = getTodayActivity();
        const auto now = QDateTime::currentDateTime();
        this->currentActivity = activityDaoPtr->create({application.id, now, now});
        for (const auto& schedule : schedules)
        {
            const auto left = timeLeft(schedule, activityToday);
            if (!left)
                continue;

            auto timer = make_shared<QTimer>();
            timer->setSingleShot(true);
            QObject::connect(timer.get(), &QTimer::timeout, [this]()
            {
                if (window)
                    window->close();
            });

            auto ms = duration_cast<milliseconds>(*left).count();
            ms += 1000;
            timer->start(static_cast<int>(min<long long>(ms, numeric_limits<int>::max())));
            timers[schedule.id] = move(timer);
        }
    }

    void ApplicationInfo::setInactive()
    {
        if (!isActive())
            return;

        for (const auto& val : timers | views::values)
            val->stop();
        timers.clear();
        updateCurrentActivityEnd();
        priorActivities.append(*currentActivity);
        currentActivity.reset();
    }
}
