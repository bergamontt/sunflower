#include "scanning/applicationscanner.h"

#include <QSettings>

class QString;

namespace sun::core
{
    class Win32ApplicationScanner : public ApplicationScanner
    {
    private:
        QList<persistence::CreateApplicationDto> doFindAll() override;
    private:
        void parseRegistry(
            const QString& root, QSettings::Format format,
            QList<persistence::CreateApplicationDto>& applications
        );
    private:
        bool isApplicationVisible(const QSettings &registry);
        persistence::CreateApplicationDto parseApplication(const QSettings &registry, const QString &key);
        QString parseExecutable(const QString& icon);
    };
} // sun::core