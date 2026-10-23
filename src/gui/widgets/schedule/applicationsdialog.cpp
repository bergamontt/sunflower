#include "applicationsdialog.h"
#include "application.h"
#include "applicationlist.h"
#include "applicationlistservice.h"
#include "ui_applicationsdialog.h"

#include <QListWidgetItem>
#include <qnamespace.h>
#include <qpushbutton.h>

ApplicationsDialog::ApplicationsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApplicationsDialog)
{
    ui->setupUi(this);
    setWindowTitle("New Application List");

    connect(
        ui->doneButton,
        &QPushButton::clicked,
        this,
        &QDialog::accept);

    connect(ui->cancelButton, 
        &QPushButton::clicked,
        this,
        &QDialog::reject);

    connect(
        ui->listName,
        &QLineEdit::textChanged,
        this,
        &ApplicationsDialog::validateForm
    );

    connect(
        ui->applicationList,
        &QListWidget::itemChanged,
        this,
        &ApplicationsDialog::validateForm
    );

    loadApplications();
    validateForm();
}

ApplicationsDialog::~ApplicationsDialog()
{
    delete ui;
}

void ApplicationsDialog::loadApplications() {
    QList<sun::persistence::Application> applications = applicationService.getAll();
    for(sun::persistence::Application application : applications) {
        QListWidgetItem *item = new QListWidgetItem(application.name);

        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        item->setData(Qt::UserRole, application.id);

        ui->applicationList->addItem(item);
    }
}

sun::persistence::ApplicationList ApplicationsDialog::getApplicationList() const
{
    sun::persistence::CreateApplicationListDto applicationListDto;
    applicationListDto.name = ui->listName->text();

    sun::persistence::ApplicationList applicationList = applicationListService.create(applicationListDto);

    for (int i = 0; i < ui->applicationList->count(); ++i) {
        QListWidgetItem *item = ui->applicationList->item(i);

        if (item->checkState() == Qt::Checked) {
            applicationListService.addApplication(applicationList.id, item->data(Qt::UserRole).toInt());
        }
    }
    return applicationList;
}

void ApplicationsDialog::validateForm()
{
    ui->doneButton->setDisabled(false);
    if(ui->listName->text().isEmpty()) ui->doneButton->setDisabled(true);
    
    int numChecked = 0;
    for (int i = 0; i < ui->applicationList->count(); ++i) {
        QListWidgetItem *item = ui->applicationList->item(i);

        if (item->checkState() == Qt::Checked) {
            ++numChecked;
        }
    }
    if(numChecked == 0) ui->doneButton->setDisabled(true);
}
