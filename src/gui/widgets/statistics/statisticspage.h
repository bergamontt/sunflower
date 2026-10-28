#ifndef STATISTICSPAGE_H
#define STATISTICSPAGE_H

#include <QWidget>
#include <QElapsedTimer>
#include <QTimer>

#include <map>
#include <set>

#include "monitoring/applicationinfo.h"

class WindowStatistics;

namespace Ui
{
    class StatisticsPage;
}

class StatisticsPage : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsPage(QWidget* parent = nullptr);
    ~StatisticsPage() override;

public slots:
    void handleApplicationDiscovered(const sun::core::ApplicationInfoDto& appInfo);
    void handleUsageStarted(const sun::core::ApplicationInfoDto& appInfo);
    void handleUsageEnded(const sun::core::ApplicationInfoDto& appInfo);

private:
    void updateApplication(const sun::core::ApplicationInfoDto& appInfo);
    void refreshWidgets();
    void refreshWidget(int id);

    Ui::StatisticsPage* ui;

    std::map<int, sun::core::ApplicationInfoDto> applications;
    std::map<int, WindowStatistics*> widgets;
    std::map<int, qint64> receivedAtMs;
    std::set<int> runningApplications;

    QElapsedTimer clock;
    QTimer refreshTimer;
};

#endif // STATISTICSPAGE_H
