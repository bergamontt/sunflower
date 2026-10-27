#include <QApplication>
#include <QFile>
#include <QDir>
#include <QStandardPaths>

#include "mainwindow.h"

#include "db/database.h"
#include "monitorfactory.h"
#include "monitoring/applicationmonitor.h"
#include "scanning/applicationscanner.h"
#include "application/applicationservice.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QApplication::setOrganizationDomain("sun");
    QApplication::setApplicationName("sunflower");

    QString data = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(data);
    QString path = data + "/sunflower.db";

    sun::persistence::Database db(path);

    sun::core::ApplicationScanner scanner;
    sun::core::ApplicationService applicationService;
    QList<sun::persistence::CreateApplicationDto> applications = scanner.findAll();
    applicationService.create(applications); 

    Q_INIT_RESOURCE(gui);
    QFile styleFile(":/gui/style.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        QString styles = QLatin1String(styleFile.readAll());
        app.setStyleSheet(styles);
        styleFile.close();
    }

    std::unique_ptr<sun::monitor::Monitor> monitorPtr = sun::monitor::createMonitor();
    sun::core::ApplicationMonitor appMonitor;

    QObject::connect(
        monitorPtr.get(),
        &sun::monitor::Monitor::usageStarted,
        &appMonitor,
        &sun::core::ApplicationMonitor::handleUsageStarted
    );

    QObject::connect(
        monitorPtr.get(),
        &sun::monitor::Monitor::usageEnded,
        &appMonitor,
        &sun::core::ApplicationMonitor::handleUsageEnded
    );

    MainWindow window;

    QObject::connect(
        &appMonitor,
        &sun::core::ApplicationMonitor::applicationDiscovered,
        window.getStatisticsPage(),
        &StatisticsPage::handleApplicationDiscovered
    );

    QObject::connect(
        &appMonitor,
        &sun::core::ApplicationMonitor::usageStarted,
        window.getStatisticsPage(),
        &StatisticsPage::handleUsageStarted
    );

    QObject::connect(
        &appMonitor,
        &sun::core::ApplicationMonitor::usageEnded,
        window.getStatisticsPage(),
        &StatisticsPage::handleUsageEnded
    );

    appMonitor.discoverApplications();
    monitorPtr->startMonitoring();

    window.show();

    return app.exec();
}