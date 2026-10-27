#pragma once

#include "application/application.h"

#include <QList>

namespace sun::core
{
    class ApplicationScanner
    {
    public:
        QList<persistence::CreateApplicationDto> findAll();
    private:
        virtual QList<persistence::CreateApplicationDto> doFindAll() = 0;
    };

    inline QList<persistence::CreateApplicationDto> ApplicationScanner::findAll()
    {
        return doFindAll();
    }
} // sun::core