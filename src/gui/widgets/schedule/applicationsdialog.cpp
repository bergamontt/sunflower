#include "applicationsdialog.h"
#include "application.h"
#include "applicationlist.h"
#include "applicationlist/applicationlistservice.h"
#include "ui_applicationsdialog.h"

#include <QListWidgetItem>
#include <qnamespace.h>
#include <qpushbutton.h>

using namespace sun::persistence;
namespace
{
    constexpr int AppId = Qt::UserRole;
}

static QIcon loadApplicationIcon(const QString& name)
{
    QIcon icon = QIcon::fromTheme(name);
    if (!icon.isNull())
        return icon;

    icon = QIcon(name);
    if (!icon.isNull())
        return icon;

    return QIcon(":/gui/exe-file.svg");
}

ApplicationsDialog::ApplicationsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApplicationsDialog)
{
    ui->setupUi(this);
    setWindowTitle("New Application List");

    connect(ui->doneButton, &QPushButton::clicked,
        this, &QDialog::accept);

    connect(ui->cancelButton, &QPushButton::clicked,
        this, &QDialog::reject);

    connect(ui->listName, &QLineEdit::textChanged,
        this, &ApplicationsDialog::validateForm);

    connect(ui->applicationList, &QListWidget::itemChanged,
        this, &ApplicationsDialog::validateForm);

    loadApplications();
}

ApplicationsDialog::~ApplicationsDialog()
{
    delete ui;
}

void ApplicationsDialog::loadApplications()
{
    const QList<Application>& applications = applicationService.getAll();
    for(const Application& application : applications)
    {
        QListWidgetItem *item = new QListWidgetItem(application.name);

        item->setIcon(loadApplicationIcon(application.icon));
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        item->setData(AppId, application.id);

        ui->applicationList->addItem(item);
    }
    ui->applicationList->sortItems(Qt::AscendingOrder);
    validateForm();
}

void ApplicationsDialog::setApplicationList(const ApplicationList& applicationList)
{
    ui->listName->setText(*applicationList.name);
    ui->listName->setProperty("listId", applicationList.id);
    const QList<Application>& applications = applicationListService.getAllApplications(applicationList.id);
    for (int i = 0; i < ui->applicationList->count(); ++i)
    {
        QListWidgetItem *item = ui->applicationList->item(i);

        for(const Application& application : applications)
        {
            if (item->data(AppId) == application.id)
            {
                item->setCheckState(Qt::Checked);
                break;
            }               
        }
    }

    setWindowTitle("Edit \"" + *applicationList.name + "\" Application List");
    validateForm();
}

ApplicationList ApplicationsDialog::getNewApplicationList() const
{
    CreateApplicationListDto applicationListDto;
    applicationListDto.name = ui->listName->text();

    QList<int> applicationIds;

    for (int i = 0; i < ui->applicationList->count(); ++i)
    {
        QListWidgetItem *item = ui->applicationList->item(i);

        if (item->checkState() == Qt::Checked)
            applicationIds.append(item->data(AppId).toInt());
    }
    return applicationListService.create(applicationListDto, applicationIds);
}

ApplicationList ApplicationsDialog::getEditedApplicationList() const
{
    UpdateApplicationListDto applicationListDto;
    applicationListDto.name = ui->listName->text();
    applicationListDto.id = ui->listName->property("listId").toInt();

    QList<int> applicationIds;

    for (int i = 0; i < ui->applicationList->count(); ++i)
    {
        QListWidgetItem *item = ui->applicationList->item(i);

        if (item->checkState() == Qt::Checked)
            applicationIds.append(item->data(AppId).toInt());
    }
    return applicationListService.updateById(applicationListDto, applicationIds);
}

void ApplicationsDialog::validateForm()
{
    ui->doneButton->setDisabled(false);
    ui->doneButton->setCursor(Qt::PointingHandCursor);
    
    int numChecked = 0;
    for (int i = 0; i < ui->applicationList->count(); ++i)
    {
        if (ui->applicationList->item(i)->checkState() == Qt::Checked)
            ++numChecked;
    }

    if(numChecked == 0 || ui->listName->text().isEmpty())
    {
        ui->doneButton->setCursor(Qt::ArrowCursor);
        ui->doneButton->setDisabled(true);
    }
}
