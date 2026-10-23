#include "applicationinfo.h"

#include <algorithm>
#include <limits>

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

    static void filterOldActivities(QList<Activity>& activities)
    {
        const QDate today = QDate::currentDate();
        erase_if(activities, [today](const Activity& activity)
        {
            return activity.startedAt.date() != today && activity.endedAt->date() != today;
        });
    }

    static optional<seconds> timeLeft(const optional<Schedule>& schedule, const seconds currentActivity)
    {
        if (!schedule || !(schedule->repeatAt & currentDayOfWeek()))
            return nullopt;

        switch (schedule->type)
        {
        case Schedule::DailyLimit:
            {
                const auto limit = seconds(*schedule->dailyLimit);
                return max(seconds::zero(), duration_cast<seconds>(limit) - currentActivity);
            }

        case Schedule::TimeWindow:
            {
                const QTime now = QTime::currentTime();
                const QTime startsAt = *schedule->startsAt;
                const QTime endsAt = *schedule->endsAt;
                const QTime midnight = QTime(23, 59, 59);

                if (startsAt <= now || now < endsAt)
                    return seconds::zero();

                if (now < startsAt)
                    seconds(now.secsTo(startsAt));
                else
                    return seconds(now.secsTo(midnight));
            }
        }

        return nullopt;
    }

    ApplicationInfo::ApplicationInfo(Application app) :
        scheduleDaoPtr(make_shared<ScheduleDao>()),
        applicationListDaoPtr(make_shared<ApplicationListDao>()),
        activityDaoPtr(make_shared<ActivityDao>()),
        activitySaveTimer(make_shared<QTimer>()),
        application(std::move(app))
    {
        QList<ApplicationList> appLists = applicationListDaoPtr->getAllByApplication(app.id);
        for (const auto& appList : appLists)
            schedules.append(scheduleDaoPtr->getAllByApplicationList(appList.id));
        QList<Activity> activities = activityDaoPtr->getAllByApplicationId(app.id);
        filterOldActivities(activities);
        priorTodayActivities = activities;

        QObject::connect(activitySaveTimer.get(), &QTimer::timeout, [this]()
        {
            updateCurrentActivityEnd();
        });
        activitySaveTimer->start(10'000);
    }

    ApplicationInfoDto ApplicationInfo::constructDto()
    {
        optional<Schedule> minSchedule;
        optional<seconds> secondsLeft;
        const seconds todayActivity = getTodayActivity();
        for (const auto& schedule : schedules)
        {
            const auto left = timeLeft(schedule, todayActivity);
            if (!secondsLeft || (left && *left < *secondsLeft))
            {
                secondsLeft = left;
                minSchedule = schedule;
            }
        }

        return ApplicationInfoDto(
            application.name,
            window ? window->getIcon() : QIcon(),
            todayActivity,
            secondsLeft,
            minSchedule ? make_optional(minSchedule->type) : nullopt
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

    seconds ApplicationInfo::getTodayActivity()
    {
        filterOldActivities(priorTodayActivities);
        const auto now = QDateTime::currentDateTime();
        const auto midnight = QDateTime(QDate::currentDate(), QTime(0, 0));
        seconds total = seconds::zero();
        for (const auto& activity : priorTodayActivities)
        {
            const auto start = max(activity.startedAt, midnight);
            total += seconds(start.secsTo(activity.endedAt.value_or(now)));
        }
        if (currentActivity)
        {
            const auto start = max(currentActivity->startedAt, midnight);
            total += seconds(start.secsTo(now));
        }
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

            const auto ms = duration_cast<milliseconds>(*left).count();
            timer->start(static_cast<int>(min<long long>(ms, numeric_limits<int>::max())));
            timers[schedule.id] = std::move(timer);
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
        priorTodayActivities.append(*currentActivity);
        currentActivity.reset();
    }
}
