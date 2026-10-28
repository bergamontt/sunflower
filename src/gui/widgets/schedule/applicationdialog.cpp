#include "applicationdialog.h"
#include "applicationlist.h"
#include "applicationsdialog.h"
#include "ui_applicationdialog.h"
#include <optional>
#include <qnamespace.h>
#include <qtreewidget.h>

using namespace sun::persistence;
namespace
{
    constexpr int ListId = Qt::UserRole;
}

ApplicationDialog::ApplicationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApplicationDialog)
{
    ui->setupUi(this);
    setWindowTitle("Create your first application list");

    connect(ui->doneButton, &QPushButton::clicked,
        this, &QDialog::accept);

    connect(ui->cancelButton, &QPushButton::clicked,
        this, &QDialog::reject);

    connect(ui->newListButton, &QPushButton::clicked,
        this, &ApplicationDialog::onNewListButtonClicked);

    connect(ui->applicationTree, &QTreeWidget::itemChanged,
        this, &ApplicationDialog::validateForm);

    loadAllApplicationLists();
}

ApplicationDialog::~ApplicationDialog()
{
    delete ui;
}

void ApplicationDialog::onNewListButtonClicked()
{
    ApplicationsDialog* applicationsDialog = new ApplicationsDialog(this);
    if(applicationsDialog->exec() == QDialog::Accepted)
    {
        ApplicationList applicationList = applicationsDialog->getApplicationList();
        insertApplicationList(applicationList);
    }
}

void ApplicationDialog::loadAllApplicationLists()
{
    ui->applicationTree->clear();
    QList<ApplicationList> allApplicationLists = applicationListService.getAll();

    for (const ApplicationList& list : allApplicationLists)
    {
        if(list.name.has_value() && !list.name->isEmpty()) insertApplicationList(list);
    }
}

void ApplicationDialog::insertApplicationList(const ApplicationList& list)
{
    QTreeWidgetItem* listItem = new QTreeWidgetItem(ui->applicationTree);

    listItem->setText(0, *list.name);
    listItem->setFlags(listItem->flags() | Qt::ItemIsUserCheckable);
    listItem->setCheckState(0, Qt::Unchecked);
    listItem->setData(0, ListId, list.id);

    const QList<Application> applications = applicationListService.getAllApplications(list.id);
    for (const Application& application : applications)
    {
        QTreeWidgetItem* applicationItem = new QTreeWidgetItem(listItem);
        applicationItem->setText(0, application.name);
    }

    listItem->setExpanded(false);
    ui->title->setText("Choose applications to block");
}

void ApplicationDialog::setSelectedApplicationLists(const QList<ApplicationList>& applicationLists)
{
    QSignalBlocker blocker(ui->applicationTree);

    // Set all to Unchecked
    for (int i = 0; i < ui->applicationTree->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem* listItem = ui->applicationTree->topLevelItem(i);
        listItem->setCheckState(0, Qt::Unchecked);
    }

    // Set selected to Checked
    for (const ApplicationList& selectedList : applicationLists)
    {
        if (selectedList.name.has_value() && !selectedList.name->isEmpty())
        {
            for (int i = 0; i < ui->applicationTree->topLevelItemCount(); ++i)
            {
                QTreeWidgetItem* listItem = ui->applicationTree->topLevelItem(i);
                const int listId = listItem->data(0, ListId).toInt();

                if (selectedList.id != listId) continue;

                listItem->setCheckState(0, Qt::Checked);
                break;
            }         
        }
    }
    validateForm();
}

QList<ApplicationList> ApplicationDialog::getSelectedApplicationLists() const
{
    QList<ApplicationList> selectedLists;

    for (int i = 0; i < ui->applicationTree->topLevelItemCount(); ++i) {
        QTreeWidgetItem* listItem = ui->applicationTree->topLevelItem(i);

        if (listItem->checkState(0) == Qt::Checked)
        {
            ApplicationList applicationList;
            applicationList.id = listItem->data(0, ListId).toInt();
            applicationList.name = listItem->text(0);
            selectedLists.append(applicationList);
        }
    }

    return selectedLists;
}

void ApplicationDialog::validateForm()
{
    ui->doneButton->setDisabled(false);

    int numChecked = 0;
    for (int i = 0; i < ui->applicationTree->topLevelItemCount(); ++i)
    {
        if (ui->applicationTree->topLevelItem(i)->checkState(0) == Qt::Checked)
            ++numChecked;
    }
    if(numChecked == 0) ui->doneButton->setDisabled(true);
}