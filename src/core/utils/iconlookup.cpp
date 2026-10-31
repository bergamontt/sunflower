#include "iconlookup.h"

namespace sun::core::utils
{
    QIcon loadApplicationIcon(const QString& name)
    {
        QIcon icon = QIcon::fromTheme(name);
        if (!icon.isNull())
            return icon;

        icon = QIcon(name);
        if (!icon.isNull())
            return icon;

        return QIcon();
    }
}