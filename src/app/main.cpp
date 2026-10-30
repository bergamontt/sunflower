#include <QApplication>
#include <QFile>
#include <QDir>
#include <QStandardPaths>

#include <memory>

#include "mainwindow.h"

#include "db/database.h"
#include "monitoring/applicationmonitor.h"
#include "scanning/applicationscanner.h"
#include "scanning/applicationscannerfactory.h"
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

    std::unique_ptr<sun::core::ApplicationScanner> scanner = sun::core::createApplicationScanner();
    QList<sun::persistence::CreateApplicationDto> applications = scanner->findAll();

    std::unique_ptr<sun::core::IApplicationService> applicationService = std::make_unique<sun::core::ApplicationService>();
    applicationService->create(applications);

    Q_INIT_RESOURCE(gui);
    QFile styleFile(":/gui/style.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        QString styles = QLatin1String(styleFile.readAll());
        app.setStyleSheet(styles);
        styleFile.close();
    }

    MainWindow window;

    sun::core::ApplicationMonitor appMonitor;

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

    window.show();

    return app.exec();
}
