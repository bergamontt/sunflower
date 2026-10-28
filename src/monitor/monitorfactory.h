#pragma once

#include <memory>
#include "monitor.h"

namespace sun::monitor
{
    std::unique_ptr<Monitor> createMonitor();
}