#include "blockwidget.h"
#include "ui_blockwidget.h"

BlockWidget::BlockWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockWidget)
{
    ui->setupUi(this);
}

BlockWidget::~BlockWidget()
{
    delete ui;
}
