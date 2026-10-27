#include "statisticspage.h"
#include "ui_statisticspage.h"
#include "windowstatistics.h"

#include <QDateTime>
#include <QIcon>
#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QChartView>
#include <QValueAxis>
#include <QPainter>
#include <QSizePolicy>
#include <QMargins>

#include <algorithm>
#include <chrono>

using namespace std::chrono;
using namespace sun::core;
using namespace sun::persistence;

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

    QChartView* createBarChart(
        const QStringList& categories,
        const QList<qreal>& values,
        qreal maxValue)
    {
        auto* set = new QBarSet("Usage");

        for (const qreal value : values)
            *set << value;

        auto* series = new QBarSeries();
        series->append(set);

        auto* chart = new QChart();
        chart->addSeries(series);
        chart->legend()->hide();
        chart->setMargins(QMargins(4, 4, 4, 4));

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

        auto* view = new QChartView(chart);
        view->setRenderHint(QPainter::Antialiasing);
        view->setSizePolicy(
            QSizePolicy::Expanding,
            QSizePolicy::Expanding);

        return view;
    }
}

StatisticsPage::StatisticsPage(QWidget* parent) : QWidget(parent), ui(new Ui::StatisticsPage)
{
    ui->setupUi(this);

    ui->weeklyGraph->addWidget(createBarChart(
        {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"},
        {1.2, 1.1, 1.0, 1.5, 1.7, 0.5, 1.0},
        2
    ));

    ui->dailyGraph->addWidget(createBarChart(
        {
            "00:00", "03:00", "06:00", "09:00",
            "12:00", "15:00", "18:00", "21:00"
        },
        {12, 8, 16, 28, 45, 38, 52, 27},
        60
    ));


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
}

void StatisticsPage::handleUsageStarted(const ApplicationInfoDto& appInfo)
{
    runningApplications.insert(appInfo.getId());
    updateApplication(appInfo);
    refreshWidget(appInfo.getId());
}

void StatisticsPage::handleUsageEnded(const ApplicationInfoDto& appInfo)
{
    updateApplication(appInfo);
    runningApplications.erase(appInfo.getId());
    refreshWidget(appInfo.getId());
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

    seconds activity = app.getTodayActivity();

    if (running)
        activity += elapsed;

    auto left = app.getTimeLeft();

    if (left)
    {
        if (app.getScheduleType() == Schedule::Type::TimeWindow)
        {
            left = std::max(seconds::zero(), *left - elapsed);
        }
        else if (app.getScheduleType() == Schedule::Type::DailyLimit
                 && running)
        {
            left = std::max(seconds::zero(), *left - elapsed);
        }
    }

    widget->setProgramName(app.getName());
    widget->setProgramIcon(app.getIcon());

    widget->setWorkTime(
        activity == seconds::zero() ? QString{} : formatDuration(activity));

    widget->setTimeLeft(left ? formatDuration(*left) : QString{});

    QString iconPath;

    if (activity > seconds::zero())
    {
        if (left.has_value() && *left == seconds::zero())
            iconPath = ":gui/alarm-yellow.svg";
        else if (running)
            iconPath = ":gui/play-green.svg";
        else
            iconPath = ":gui/pause-grey.svg";
    }

    widget->setWorkTimeIconPath(iconPath);
}
