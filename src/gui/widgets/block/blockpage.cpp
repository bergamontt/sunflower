#include "blockpage.h"
#include "ui_blockpage.h"

BlockPage::BlockPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockPage)
{
    ui->setupUi(this);
}

BlockPage::~BlockPage()
{
    delete ui;
}
