#include "scanning/applicationscanner.h"

namespace sun::core
{
    class Win32ApplicationScanner : public ApplicationScanner
    {
    private:
        QList<persistence::CreateApplicationDto> doFindAll() override;
    };
} // sun::core