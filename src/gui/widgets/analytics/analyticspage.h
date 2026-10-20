#ifndef ANALYTICSPAGE_H
#define ANALYTICSPAGE_H

#include <QWidget>

namespace Ui {
class AnalyticsPage;
}

class AnalyticsPage : public QWidget
{
    Q_OBJECT

public:
    explicit AnalyticsPage(QWidget *parent = nullptr);
    ~AnalyticsPage();

private:
    Ui::AnalyticsPage *ui;
};

#endif // ANALYTICSPAGE_H
