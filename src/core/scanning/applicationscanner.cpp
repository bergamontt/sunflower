#include "scanning/applicationscanner.h"

#include <QSettings>
#include <QStandardPaths>
#include <QDirIterator>
#include <QDir>

namespace sun::core
{
    using namespace sun::persistence;

    QList<persistence::CreateApplicationDto> ApplicationScanner::findAll()
    {
        QList<CreateApplicationDto> applications;
        auto dirs = QStandardPaths::standardLocations(QStandardPaths::ApplicationsLocation);
        for (const QString &dir : dirs) {
            QDirIterator it(dir, {"*.desktop"}, QDir::Files, QDirIterator::Subdirectories);
            while (it.hasNext())
            {
                QSettings file(it.next(), QSettings::IniFormat);
                file.beginGroup("Desktop Entry");
                if (isApplicationHidden(file))
                    continue;
                applications.append(parseApplication(file));
            }
        }
        return applications;
    }

    persistence::CreateApplicationDto ApplicationScanner::parseApplication(const QSettings &file)
    {
        QString name = file.value("Name").toString();
        QString exec = file.value("Exec").toString();
        QString icon = file.value("Icon").toString();
        return {name, exec, icon};
    }

    bool ApplicationScanner::isApplicationHidden(const QSettings &file)
    {
        return file.value("NoDisplay").toBool() || file.value("Hidden").toBool();
    }
} // sun::core