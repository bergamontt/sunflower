#ifndef ANALYTICSPAGE_H
#define ANALYTICSPAGE_H

#include <QWidget>

namespace Ui {
class AnalyticsWidget;
}

class AnalyticsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AnalyticsWidget(QWidget *parent = nullptr);
    ~AnalyticsWidget();

private:
    Ui::AnalyticsWidget *ui;
};

#endif // ANALYTICSPAGE_H
