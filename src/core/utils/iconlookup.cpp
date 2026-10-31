#include "iconlookup.h"

#include <QFileIconProvider>
#include <QFileInfo>

namespace sun::core::utils
{
    namespace
    {
        QString cleanPath(const QString& path)
        {
            return path.section(',', 0, 0).remove('"').trimmed();
        }

        QIcon loadFromFileProvider(const QString& path)
        {
            const QFileInfo info(cleanPath(path));
            if (!info.exists())
            {
                return QIcon();
            }
            return QFileIconProvider().icon(info);
        }
    } // namespace

    QIcon loadApplicationIcon(const QString& name)
    {
        QIcon icon = QIcon::fromTheme(name);
        if (!icon.isNull())
        {
            return icon;
        }
        icon = QIcon(name);
        if (!icon.isNull())
        {
            return icon;
        }
        return loadFromFileProvider(name);
    }
} // namespace sun::core::utils