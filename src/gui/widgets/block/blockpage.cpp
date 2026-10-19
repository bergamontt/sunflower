#include "blockpage.h"
#include "ui_blockpage.h"

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
