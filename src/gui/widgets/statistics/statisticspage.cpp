#include "statisticspage.h"
#include "ui_statisticspage.h"

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QChartView>
#include <QValueAxis>
#include <QStringList>
#include <QPainter>
#include <windowstatistics.h>

static QChartView* createBarChart(const QStringList& categories, const QList<qreal>& values, qreal maxValue);

StatisticsPage::StatisticsPage(QWidget* parent)
    : QWidget(parent),
    ui(new Ui::StatisticsPage)
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

    struct ProgramUsage
    {
        QString name;
        QString iconPath;
        QString workTime;
        QString workTimeIconPath;
        QString status;
    };

    const QList<ProgramUsage> programs = {
        {
            "Visual Studio Code",
            ":gui/pause-grey.svg",
            "02:14:17",
            ":gui/pause-grey.svg",
            "37 min left"
        },
        {
            "Firefox",
            ":gui/alarm-yellow.svg",
            "03:00:00",
            ":gui/alarm-yellow.svg",
            "Time limit reached"
        },
        {
            "Terminal",
            ":gui/play-green.svg",
            "01:08:22",
            ":gui/play-green.svg",
            ""
        }
    };

    for (const ProgramUsage& program : programs)
    {
        auto* item = new WindowStatistics(this);

        item->setProgramName(program.name);
        item->setProgramIconPath(program.iconPath);
        item->setWorkTime(program.workTime);
        item->setWorkTimeIconPath(program.workTimeIconPath);
        item->setStatus(program.status);

        ui->windowsList->addWidget(item);
    }
}

StatisticsPage::~StatisticsPage()
{
    delete ui;
}

static QChartView* createBarChart(const QStringList& categories, const QList<qreal>& values, qreal maxValue)
{
    auto* set = new QBarSet("Usage");

    for (qreal value : values)
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
