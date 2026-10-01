#pragma once

#include "application/application.h"

namespace sun::persistence 
{
    class ApplicationDao
    {
    public:    
        Application create(const CreateApplicationDto& dto);
        Application updateById(const UpdateApplicationDto& dto);
        Application getById(int id);
        void deleteById(int id);
    };
}