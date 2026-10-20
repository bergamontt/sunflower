#include "appearancesection.h"
#include "ui_appearancesection.h"

AppearanceSection::AppearanceSection(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::AppearanceSection)
{
    ui->setupUi(this);
}

AppearanceSection::~AppearanceSection()
{
    delete ui;
}
