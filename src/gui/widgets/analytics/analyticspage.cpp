#include "analyticspage.h"
#include "ui_analyticspage.h"

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
