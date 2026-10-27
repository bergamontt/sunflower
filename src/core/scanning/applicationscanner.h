#pragma once

#include "application/application.h"

#include <QList>

class QSettings;

namespace sun::core
{
    class ApplicationScanner
    {
    public:
        QList<persistence::CreateApplicationDto> findAll();
    private:
        persistence::CreateApplicationDto parseApplication(const QSettings& file);
        bool isApplicationHidden(const QSettings& file);
    };
} // sun::core