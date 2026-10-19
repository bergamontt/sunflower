#include "analyticswidget.h"
#include "ui_analyticswidget.h"

AnalyticsWidget::AnalyticsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalyticsWidget)
{
    ui->setupUi(this);
}

AnalyticsWidget::~AnalyticsWidget()
{
    delete ui;
}
