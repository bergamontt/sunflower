#include "applicationshortlist.h"
#include "ui_applicationshortlist.h"

ApplicationShortList::ApplicationShortList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApplicationShortList)
{
    ui->setupUi(this);
}

ApplicationShortList::~ApplicationShortList()
{
    delete ui;
}
