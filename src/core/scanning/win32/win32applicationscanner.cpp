#include "scanning/win32/win32applicationscanner.h"

#include <QSettings>
#include <QString>
#include <QList>
#include <QStringList>

namespace sun::core
{
    using namespace sun::persistence;

    namespace
    {
        const inline QString path = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall";
        const inline QStringList roots = {"HKEY_LOCAL_MACHINE", "HKEY_CURRENT_USER"};
        const inline QList<QSettings::Format> formats = {QSettings::Registry32Format, QSettings::Registry64Format};
    }

    QList<CreateApplicationDto> Win32ApplicationScanner::doFindAll()
    {
        QList<CreateApplicationDto> applications;
        for (const auto& root : roots)
        {
            for (const auto& format : formats)
            {
                parseRegistry(root, format, applications);
            }
        }
        return applications;
    }

    void Win32ApplicationScanner::parseRegistry(
        const QString& root, QSettings::Format format,
        QList<persistence::CreateApplicationDto>& applications
    ) {
        QSettings registry(root + "\\" + path, format);
        for (const auto& key : registry.childGroups())
        {
            registry.beginGroup(key);
            if (isApplicationVisible(registry))
            {
                applications.append(parseApplication(registry, key));
            }
            registry.endGroup();
        }
    }

    bool Win32ApplicationScanner::isApplicationVisible(const QSettings &registry)
    {
        return !registry.value("DisplayName").toString().isEmpty() &&
            !registry.value("SystemComponent").toInt() == 1;
    }

    persistence::CreateApplicationDto Win32ApplicationScanner::parseApplication(const QSettings &registry, const QString &key)
    {
        QString name = registry.value("DisplayName").toString();
        QString icon = registry.value("DisplayIcon").toString();
        QString executable = parseExecutable(icon);
        if (executable.isEmpty())
        {
            executable = name;
        }
        return {name, executable, icon, key};
    }

    QString Win32ApplicationScanner::parseExecutable(const QString &icon)
    {
        return icon.section(',', 0, 0).remove('"').trimmed();
    }
}