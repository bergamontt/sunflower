#include "linuxapplicationscanner.h"

#include <QSettings>
#include <QStandardPaths>
#include <QDirIterator>
#include <QDir>

namespace sun::core
{
    using namespace sun::persistence;

    QList<persistence::CreateApplicationDto> LinuxApplicationScanner::doFindAll()
    {
        QList<CreateApplicationDto> applications;
        auto dirs = QStandardPaths::standardLocations(QStandardPaths::ApplicationsLocation);
        for (const QString &dir : dirs) {
            QDirIterator it(dir, {"*.desktop"}, QDir::Files, QDirIterator::Subdirectories);
            while (it.hasNext())
            {
                QString path = it.next();
                QString source = parseSource(dir, path);
                QSettings file(path, QSettings::IniFormat);
                file.beginGroup("Desktop Entry");
                if (isApplicationHidden(file))
                    continue;
                applications.append(parseApplication(file, source));
            }
        }
        return applications;
    }

    persistence::CreateApplicationDto LinuxApplicationScanner::parseApplication(
        const QSettings &file, const QString& source
    ) {
        QString name = file.value("Name").toString();
        QString exec = file.value("Exec").toString();
        QString icon = file.value("Icon").toString();
        return {name, exec, icon, source};
    }

    QString LinuxApplicationScanner::parseSource(const QDir& dir, const QString& path)
    {
        return dir.relativeFilePath(path).replace('/', '-');
    }

    bool LinuxApplicationScanner::isApplicationHidden(const QSettings &file)
    {
        return file.value("NoDisplay").toBool() || file.value("Hidden").toBool();
    }
} // sun::core