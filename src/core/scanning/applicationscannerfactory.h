#pragma once

#include "scanning/applicationscanner.h"

#include <memory>

namespace sun::core
{
    std::unique_ptr<ApplicationScanner> createApplicationScanner();
} // sun::core