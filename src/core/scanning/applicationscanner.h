#pragma once

#include "application/application.h"

#include <QList>
#include <QString>

class QSettings;
class QDir;

namespace sun::core
{
    class ApplicationScanner
    {
    public:
        QList<persistence::CreateApplicationDto> findAll();
    private:
        persistence::CreateApplicationDto parseApplication(const QSettings& file, const QString& source);
        QString parseSource(const QDir& dir, const QString& path);
        bool isApplicationHidden(const QSettings& file);
    };
} // sun::core