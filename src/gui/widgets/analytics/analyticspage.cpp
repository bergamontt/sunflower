#include "analyticspage.h"
#include "ui_analyticspage.h"

AnalyticsPage::AnalyticsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalyticsPage)
{
    ui->setupUi(this);
}

AnalyticsPage::~AnalyticsPage()
{
    delete ui;
}
