#pragma once

#include "application/applicationdao.h"

#include <QList>

namespace sun::core
{
    class ApplicationService
    {
    public:
        persistence::Application create(const persistence::CreateApplicationDto& dto);
        QList<persistence::Application> create(const QList<persistence::CreateApplicationDto>& dtos);
    private:
        persistence::ApplicationDao applicationDao;
    };
} // sun::core