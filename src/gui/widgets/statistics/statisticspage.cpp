#include "statisticspage.h"
#include "ui_statisticspage.h"
#include "windowstatistics.h"
#include "monitoring/applicationmonitor.h"

#include <QChartView>
#include <QChart>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QValueAxis>
#include <QPainter>
#include <QSizePolicy>
#include <QMargins>
#include <QVBoxLayout>
#include <QTimeZone>
#include <QSystemTrayIcon>
#include <QApplication>

using namespace std;
using namespace std::chrono;
using namespace sun::core;
using namespace sun::persistence;

struct UsageBarChart
{
    QChartView* view;
    QChart* chart;
    QBarSet* barSet;
    QBarCategoryAxis* axisX;
    QValueAxis* axisY;
};

namespace
{
    QString formatDuration(seconds duration)
    {
        const auto total = std::max<qint64>(0, duration.count());
        const auto hours = total / 3600;
        const auto minutes = (total % 3600) / 60;
        const auto secs = total % 60;

        return QString("%1:%2:%3")
            .arg(hours, 2, 10, QChar('0'))
            .arg(minutes, 2, 10, QChar('0'))
            .arg(secs, 2, 10, QChar('0'));
    }

    UsageBarChart* createBarChart(
        const QStringList& categories,
        const QList<qreal>& values,
        qreal maxValue)
    {
        auto* barSet = new QBarSet("Usage");

        for (const qreal value : values)
            *barSet << value;

        auto* series = new QBarSeries();
        series->append(barSet);

        auto* chart = new QChart();
        chart->addSeries(series);
        chart->legend()->hide();
        chart->setMargins(QMargins(4, 4, 4, 4));
        chart->setBackgroundRoundness(10);
        chart->setAnimationOptions(QChart::NoAnimation);

        auto* axisX = new QBarCategoryAxis();
        axisX->append(categories);
        axisX->setGridLineVisible(false);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        auto* axisY = new QValueAxis();
        axisY->setRange(0, maxValue);
        axisY->setTickInterval(maxValue / 5);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        axisX->setLabelsColor(Qt::black);
        axisY->setLabelsColor(Qt::black);

        axisX->setTitleBrush(Qt::black);
        axisY->setTitleBrush(Qt::black);

        auto* view = new QChartView(chart);
        view->setRenderHint(QPainter::Antialiasing);
        view->setSizePolicy(
            QSizePolicy::Expanding,
            QSizePolicy::Expanding);
        view->setBackgroundBrush(Qt::NoBrush);
        view->viewport()->setAutoFillBackground(false);

        return new UsageBarChart{
            view,
            chart,
            barSet,
            axisX,
            axisY
        };
    }

    void updateChart(
        UsageBarChart* chart,
        const QStringList& categories,
        const QList<qreal>& values,
        qreal maxValue)
    {
        if (!chart)
            return;

        chart->barSet->remove(0, chart->barSet->count());
        for (const qreal value : values)
            *chart->barSet << value;

        if (chart->axisX->categories() != categories)
        {
            chart->axisX->clear();
            chart->axisX->append(categories);
        }

        if (chart->axisY->max() != maxValue)
        {
            chart->axisY->setRange(0, maxValue);
            chart->axisY->setTickInterval(maxValue / 5);
        }
    }

    struct Interval
    {
        QDateTime start;
        QDateTime end;
    };

    void mergeIntervals(QList<Interval>& intervals)
    {
        sort(
            intervals.begin(),
            intervals.end(),
            [](const Interval& a, const Interval& b) { return a.start < b.start; }
        );
        QList<Interval> merged;
        for (const auto& interval : intervals)
        {
            if (merged.isEmpty() || interval.start > merged.last().end)
            {
                merged.append(interval);
            }
            else if (interval.end > merged.last().end)
            {
                merged.last().end = interval.end;
            }
        }
        intervals = move(merged);
    };
}

StatisticsPage::StatisticsPage(QWidget* parent) : QWidget(parent), ui(new Ui::StatisticsPage)
{
    ui->setupUi(this);

    auto& appMonitor = sun::core::ApplicationMonitor::instance();

    QObject::connect(
        &appMonitor,
        &sun::core::ApplicationMonitor::applicationDiscovered,
        this,
        &StatisticsPage::handleApplicationDiscovered
    );

    QObject::connect(
        &appMonitor,
        &sun::core::ApplicationMonitor::usageStarted,
        this,
        &StatisticsPage::handleUsageStarted
    );

    QObject::connect(
        &appMonitor,
        &sun::core::ApplicationMonitor::usageEnded,
        this,
        &StatisticsPage::handleUsageEnded
    );

    weeklyChart = createBarChart(
        {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"},
        {0, 0, 0, 0, 0, 0, 0},
        24
    );
    dailyChart = createBarChart(
        {
            "00:00", "03:00", "06:00", "09:00",
            "12:00", "15:00", "18:00", "21:00"
        },
        {0, 0, 0, 0, 0, 0, 0, 0},
        180
    );

    ui->weeklyGraph->addWidget(weeklyChart->view);
    ui->dailyGraph->addWidget(dailyChart->view);

    clock.start();
    connect(&refreshTimer, &QTimer::timeout, this, &StatisticsPage::refreshWidgets);
    refreshTimer.start(1000);
}

StatisticsPage::~StatisticsPage()
{
    delete ui;
}

void StatisticsPage::handleApplicationDiscovered(const ApplicationInfoDto& appInfo)
{
    updateApplication(appInfo);
    refreshWidget(appInfo.getId());
    sortWidgets();
    refreshGraphs();
}

void StatisticsPage::handleUsageStarted(const ApplicationInfoDto& appInfo)
{
    runningApplications.insert(appInfo.getId());
    updateApplication(appInfo);
    refreshWidget(appInfo.getId());
    sortWidgets();
    refreshGraphs();
}

void StatisticsPage::handleUsageEnded(const ApplicationInfoDto& appInfo)
{
    updateApplication(appInfo);
    runningApplications.erase(appInfo.getId());
    refreshWidget(appInfo.getId());
    refreshGraphs();

    const auto timeLeft = appInfo.getTimeLeft();
    if (timeLeft && *timeLeft == seconds::zero())
        sendTimeoutNotificaion(appInfo);
}

void StatisticsPage::updateApplication(const ApplicationInfoDto& appInfo)
{
    const int id = appInfo.getId();

    applications.insert_or_assign(id, appInfo);
    receivedAtMs.insert_or_assign(id, clock.elapsed());

    auto it = widgets.find(id);

    if (it == widgets.end())
    {
        auto* widget = new WindowStatistics(this);
        ui->windowsList->addWidget(widget);

        widgets.emplace(id, widget);
    }

    refreshWidget(id);
}

void StatisticsPage::sendTimeoutNotificaion(const sun::core::ApplicationInfoDto& appInfo)
{
    if (!QSystemTrayIcon::isSystemTrayAvailable())
        return;

    auto* trayIcon = new QSystemTrayIcon(appInfo.getIcon(), this);

    trayIcon->show();
    trayIcon->showMessage(
        "Time limit reached",
        QString("Your allowed time for %1 has ended.")
            .arg(appInfo.getName()),
        QSystemTrayIcon::Warning,
        5000
    );

    connect(
        trayIcon,
        &QSystemTrayIcon::messageClicked,
        trayIcon,
        &QObject::deleteLater
    );

    QTimer::singleShot(6000, trayIcon, &QObject::deleteLater);
}

void StatisticsPage::refreshWidgets()
{
    for (const auto& [id, appInfo] : applications)
        refreshWidget(id);
}

void StatisticsPage::refreshWidget(const int id)
{
    const auto appIt = applications.find(id);
    const auto widgetIt = widgets.find(id);

    if (appIt == applications.end() || widgetIt == widgets.end())
        return;

    const auto& app = appIt->second;
    auto* widget = widgetIt->second;

    const bool running = runningApplications.contains(id);

    const auto elapsedMs = clock.elapsed() - receivedAtMs.at(id);
    const seconds elapsed(elapsedMs / 1000);

    optional<seconds> activity = app.getTodayActivity();

    if (running && activity)
        *activity += elapsed;

    auto left = app.getTimeLeft();

    if (left)
    {
        if (app.getScheduleType() == Schedule::Type::TimeWindow)
        {
            left = max(seconds::zero(), *left - elapsed);
        }
        else if (app.getScheduleType() == Schedule::Type::DailyLimit && running)
        {
            left = max(seconds::zero(), *left - elapsed);
        }
    }

    widget->setProgramName(app.getName());
    widget->setProgramIcon(app.getIcon());
    widget->setWorkTime(activity ? formatDuration(*activity) : QString());
    widget->setTimeLeft(left ? formatDuration(*left) : QString{});

    QString iconPath;

    if (activity)
    {
        if (left && *left == seconds::zero())
            iconPath = ":gui/alarm-yellow.svg";
        else if (running)
            iconPath = ":gui/play-green.svg";
        else
            iconPath = ":gui/pause-grey.svg";
    }

    widget->setWorkTimeIconPath(iconPath);
}


void StatisticsPage::refreshGraphs()
{
    if (!ui->weeklyGraph || !ui->dailyGraph)
        return;

    const QDate today = QDate::currentDate();
    const QDate monday = today.addDays(1 - today.dayOfWeek());
    const QDateTime now = QDateTime::currentDateTime();

    array<seconds, 7> weeklyUsage{};
    array<seconds, 8> dailyUsage{};

    QList<Interval> weeklyIntervals;
    QList<Interval> dailyIntervals;

    for (const auto& [id, appInfo] : applications)
    {
        for (const auto& activity : appInfo.getActivityHistory())
        {
            const QDateTime start = activity.startedAt;

            const QDateTime end = activity.endedAt.value_or(
                runningApplications.contains(id) ? now : start);

            if (!start.isValid() || !end.isValid() || end <= start)
                continue;

            const QDate firstDate = max(start.date(), monday);
            const QDate lastDate = min(end.date(), today);

            for (QDate date = firstDate; date <= lastDate; date = date.addDays(1))
            {
                const QDateTime dayStart(
                    date, QTime(0, 0), start.timeZone());

                const QDateTime dayEnd = date == today
                    ? now
                    : QDateTime(
                        date.addDays(1), QTime(0, 0), start.timeZone());

                const QDateTime intervalStart = max(start, dayStart);
                const QDateTime intervalEnd = min(end, dayEnd);

                if (intervalEnd <= intervalStart)
                    continue;

                weeklyIntervals.append({intervalStart, intervalEnd});

                if (date == today)
                    dailyIntervals.append({intervalStart, intervalEnd});
            }
        }
    }

    mergeIntervals(weeklyIntervals);
    mergeIntervals(dailyIntervals);

    for (const auto& interval : weeklyIntervals)
    {
        QDateTime cursor = interval.start;

        while (cursor < interval.end)
        {
            const QDate date = cursor.date();
            const QDateTime nextDay(date.addDays(1), QTime(0, 0), cursor.timeZone());
            const QDateTime segmentEnd = min(interval.end, nextDay);
            weeklyUsage[date.dayOfWeek() - 1] += seconds(cursor.secsTo(segmentEnd));
            cursor = segmentEnd;
        }
    }

    for (const auto& interval : dailyIntervals)
    {
        QDateTime cursor = interval.start;

        while (cursor < interval.end)
        {
            const int bucket = cursor.time().hour() / 3;
            const int nextBucketHour = (bucket + 1) * 3;
            const QDateTime nextBoundary = QDateTime(
                cursor.date(),
                QTime(nextBucketHour % 24, 0),
                cursor.timeZone()
            ).addDays(nextBucketHour / 24);
            const QDateTime segmentEnd = min(interval.end, nextBoundary);
            dailyUsage[bucket] += seconds(cursor.secsTo(segmentEnd));
            cursor = segmentEnd;
        }
    }

    QStringList weeklyCategories;
    QList<qreal> weeklyValues;

    for (int i = 0; i < 7; ++i)
    {
        weeklyCategories.append(monday.addDays(i).toString("ddd"));
        weeklyValues.append(weeklyUsage[i].count() / 3600.0);
    }

    QStringList dailyCategories;
    QList<qreal> dailyValues;

    for (int i = 0; i < 8; ++i)
    {
        dailyCategories.append(QString("%1:00").arg(i * 3, 2, 10, QChar('0')));
        dailyValues.append(dailyUsage[i].count() / 60.0);
    }

    const qreal weeklyMax = max<qreal>(
        1.0,
        ceil(*max_element(
            weeklyValues.begin(), weeklyValues.end())));

    const qreal dailyMax = max<qreal>(
        180.0,
        ceil(*max_element(
            dailyValues.begin(), dailyValues.end()) / 30.0) * 30.0);

    updateChart(weeklyChart, weeklyCategories, weeklyValues, weeklyMax);
    updateChart(dailyChart, dailyCategories, dailyValues, dailyMax);
}

void StatisticsPage::sortWidgets()
{
    vector<int> ids;
    ids.reserve(applications.size());

    for (const auto& [id, appInfo] : applications)
        ids.push_back(id);

    sort(ids.begin(), ids.end(), [this](const int lhs, const int rhs)
    {
        const auto lhsTime = applications.at(lhs).getTodayActivity();
        const auto rhsTime = applications.at(rhs).getTodayActivity();

        if (lhsTime != rhsTime)
            return lhsTime > rhsTime;

        const QString& lhsName = applications.at(lhs).getName();
        const QString& rhsName = applications.at(rhs).getName();

        const int comparison = QString::compare(
            lhsName,
            rhsName,
            Qt::CaseInsensitive
        );
        return comparison < 0;
    });

    for (int i = 0; i < static_cast<int>(ids.size()); ++i)
    {
        auto* widget = widgets.at(ids[i]);
        ui->windowsList->removeWidget(widget);
        ui->windowsList->insertWidget(i, widget);
    }
}