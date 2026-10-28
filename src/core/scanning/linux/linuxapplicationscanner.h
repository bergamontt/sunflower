#pragma once

#include "scanning/applicationscanner.h"
#include "application/application.h"

#include <QList>
#include <QString>

class QSettings;
class QDir;

namespace sun::core
{
    class LinuxApplicationScanner : public ApplicationScanner
    {
    private:
        QList<persistence::CreateApplicationDto> doFindAll() override;
    private:
        persistence::CreateApplicationDto parseApplication(const QSettings& file, const QString& source);
        QString parseSource(const QDir& dir, const QString& path);
        bool isApplicationHidden(const QSettings& file);
    };
} // sun::core