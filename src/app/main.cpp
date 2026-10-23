#include <QApplication>
#include <QFile>
#include <QDir>
#include <QStandardPaths>

#include "mainwindow.h"

#include "db/database.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QApplication::setOrganizationDomain("sun");
    QApplication::setApplicationName("sunflower");

    QString data = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(data);
    QString path = data + "/sunflower.db";

    sun::persistence::Database db(path);

    Q_INIT_RESOURCE(gui);
    QFile styleFile(":/gui/style.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        QString styles = QLatin1String(styleFile.readAll());
        app.setStyleSheet(styles);
        styleFile.close();
    }

    MainWindow window;
    window.show();

    return app.exec();
}