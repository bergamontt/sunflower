#ifndef ANALYTICSWIDGET_H
#define ANALYTICSWIDGET_H

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

#endif // ANALYTICSWIDGET_H
