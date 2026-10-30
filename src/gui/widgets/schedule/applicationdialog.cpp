#include "applicationdialog.h"
#include "applicationlist.h"
#include "applicationlist/applicationlistservice.h"
#include "applicationsdialog.h"
#include "deletedialog.h"
#include "ui_applicationdialog.h"
#include "schedule/scheduleservice.h"
#include <optional>
#include <qicon.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qtreewidget.h>

using namespace sun::persistence;
using namespace sun::core;

namespace
{
    constexpr int ListId = Qt::UserRole;
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

ApplicationDialog::ApplicationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApplicationDialog),
    applicationListService(std::make_unique<ApplicationListService>()),
    scheduleService(std::make_unique<ScheduleService>())
{
    ui->setupUi(this);
    setWindowTitle("Application lists");
    ui->title->setText("Create your first application list");

    ui->applicationTree->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->applicationTree->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);

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
        ApplicationList applicationList = applicationsDialog->getNewApplicationList();
        insertApplicationList(applicationList);
    }
}

void ApplicationDialog::loadAllApplicationLists()
{
    ui->applicationTree->clear();
    QList<ApplicationList> allApplicationLists = applicationListService->getAll();

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
    setUpAppListButtons(listItem, list);

    const QList<Application> applications = applicationListService->getAllApplications(list.id);
    for (const Application& application : applications)
    {
        QTreeWidgetItem* applicationItem = new QTreeWidgetItem(listItem);
        applicationItem->setIcon(0, loadApplicationIcon(application.icon));
        applicationItem->setText(0, application.name);
    }

    listItem->setExpanded(false);
    listItem->sortChildren(0, Qt::AscendingOrder);

    ui->title->setText("Choose applications to block");
    ui->applicationTree->sortItems(0, Qt::AscendingOrder);
}

void ApplicationDialog::setUpAppListButtons(QTreeWidgetItem *listItem, const ApplicationList& list)
{
    auto *buttons = new QWidget();
    auto *layout = new QHBoxLayout(buttons);
    buttons->setProperty("widgetClass", "background");
    layout->setContentsMargins(0, 0, 0, 0);

    auto *editButton = new QPushButton(QIcon(":/gui/edit.svg"), "");
    editButton->setProperty("buttonClass", "editAppList");
    editButton->setMinimumSize(20, 20);
    connect(editButton, &QPushButton::clicked,
        this, [this, list](){onEditButtonClicked(list);});
    layout->addWidget(editButton);

    auto *deleteButton = new QPushButton(QIcon(":/gui/delete.svg"), "");
    deleteButton->setProperty("buttonClass", "deleteAppList");
    deleteButton->setMinimumSize(20, 20);
    connect(deleteButton, &QPushButton::clicked,
        this, [this, list](){onDeleteButtonClicked(list.id, *list.name);} );
    layout->addWidget(deleteButton);

    if(!scheduleService->getAllByApplicationList(list.id).empty())
    {
        deleteButton->setDisabled(true);
        deleteButton->setCursor(Qt::ArrowCursor);
        deleteButton->setToolTip("Can't delete a list while there are schedules that use it");
    }

    ui->applicationTree->setItemWidget(listItem, 1, buttons);
}

void ApplicationDialog::onEditButtonClicked(const ApplicationList& list)
{
    ApplicationsDialog* dialog = new ApplicationsDialog(this);
    dialog->setApplicationList(list);

    if(dialog->exec() == QDialog::Accepted)
    {
        const ApplicationList& updatedList = dialog->getEditedApplicationList();
        removeApplicationListItemById(list.id);
        insertApplicationList(updatedList);
    }
}

void ApplicationDialog::onDeleteButtonClicked(int listId, QString listName)
{
    DeleteDialog* deleteDialog = new DeleteDialog(this);
    deleteDialog->setItem(listName);

    if(deleteDialog->exec() == QDialog::Accepted)
    {
        applicationListService->deleteById(listId);
        removeApplicationListItemById(listId);
    }
}

void ApplicationDialog::removeApplicationListItemById(int id)
{
    for (int i = 0; i < ui->applicationTree->topLevelItemCount(); ++i)
    {
        if(ui->applicationTree->topLevelItem(i)->data(0, ListId) == id)
        {
            delete ui->applicationTree->takeTopLevelItem(i);
            break;
        }
    }
    validateForm();
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
    ui->doneButton->setCursor(Qt::PointingHandCursor);

    int numChecked = 0;
    for (int i = 0; i < ui->applicationTree->topLevelItemCount(); ++i)
    {
        if (ui->applicationTree->topLevelItem(i)->checkState(0) == Qt::Checked)
            ++numChecked;
    }
    if(numChecked == 0)
    {
        ui->doneButton->setCursor(Qt::ArrowCursor);
        ui->doneButton->setDisabled(true);
    }
    
}
