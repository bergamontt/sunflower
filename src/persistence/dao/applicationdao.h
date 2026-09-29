#pragma once

#include "../model/application.h"

namespace sun::persistence 
{
    class ApplicationDao
    {
    public:    
        Application create(const Application& application);
        Application updateById(int id, const Application& application);
        Application getById(int id);
        void deleteById(int id);
    };
}