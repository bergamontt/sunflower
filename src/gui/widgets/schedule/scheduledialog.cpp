#include "scheduledialog.h"
#include "ui_scheduledialog.h"

#include <QButtonGroup>
#include <QStyle>

ScheduleDialog::ScheduleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScheduleDialog)
{
    ui->setupUi(this);

    setWindowTitle("Create new Schedule");

    ui->blockButton->setCheckable(true);
    ui->limitButton->setCheckable(true);

    auto *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->blockButton);
    buttonGroup->addButton(ui->limitButton);
    buttonGroup->setExclusive(true);

    ui->blockButton->setChecked(true);
    ui->blockTypeContainer->setCurrentIndex(0);

    connect(ui->blockButton, &QPushButton::clicked, this, [this]()
    {
        ui->blockTypeContainer->setCurrentIndex(0);
    });

    connect(ui->limitButton, &QPushButton::clicked, this, [this]()
    {
        ui->blockTypeContainer->setCurrentIndex(1);
    });

    for (QWidget *widget : ui->blockTypeContainer->findChildren<QWidget *>()) {
        widget->style()->unpolish(widget);
        widget->style()->polish(widget);
        widget->update();
    }

    resize(435, 463);
}

ScheduleDialog::~ScheduleDialog()
{
    delete ui;
}
