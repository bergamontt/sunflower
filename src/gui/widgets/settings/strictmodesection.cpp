#include "strictmodesection.h"
#include "ui_strictmodesection.h"

StrictModeSection::StrictModeSection(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::StrictModeSection)
{
    ui->setupUi(this);
    connect(ui->strictModeComboBox, &QComboBox::currentIndexChanged, this, &StrictModeSection::updateSettingsSectionSize);
    updatePasswordSettings(true);
    updateSettingsSectionSize(ui->settingsStrictMode->currentIndex());
}

StrictModeSection::~StrictModeSection()
{
    delete ui;
}

void StrictModeSection::updateSettingsSectionSize(int index)
{
    QStackedWidget* stack = ui->settingsStrictMode;
    for (int i = 0; i < stack->count(); ++i)
    {
        QWidget* page = stack->widget(i);
        QSizePolicy::Policy policy = (i == index) ? QSizePolicy::Preferred : QSizePolicy::Ignored;
        page->setSizePolicy(policy, policy);
    }
    stack->setCurrentIndex(index);
    stack->updateGeometry();
    adjustSize();
}

void StrictModeSection::updatePasswordSettings(bool hasPassword)
{
    ui->newPasswordLabel->setVisible(hasPassword);
    ui->newPasswordLineEdit->setVisible(hasPassword);
}
