#include "applicationdialog.h"
#include "applicationlist.h"
#include "applicationsdialog.h"
#include "ui_applicationdialog.h"
#include <optional>
#include <qnamespace.h>

namespace
{
    constexpr int ItemTypeRole = Qt::UserRole;
    constexpr int ListIdRole = Qt::UserRole + 1;
    constexpr int ApplicationIdRole = Qt::UserRole + 2;

    constexpr int ListItemType = 1;
    constexpr int ApplicationItemType = 2;
}

ApplicationDialog::ApplicationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApplicationDialog)
{
    ui->setupUi(this);
    setWindowTitle("Select Applications");

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
        ui->applicationTree,
        &QTreeWidget::itemChanged,
        this,
        &ApplicationDialog::onItemChanged
    );

    connect(
        ui->newListButton,
        &QPushButton::clicked,
        this,
        [this](){
            ApplicationsDialog applicationsDialog;
            if(applicationsDialog.exec() == QDialog::Accepted) {
                sun::persistence::ApplicationList applicationList = applicationsDialog.getApplicationList();
                ui->title->setText("Choose applications to block");
                insertApplicationList(applicationList);
            }
        }

    );

    loadApplicationLists();
}

ApplicationDialog::~ApplicationDialog()
{
    delete ui;
}

void ApplicationDialog::loadApplicationLists()
{
    ui->applicationTree->clear();
    QList<sun::persistence::ApplicationList> allApplicationLists = applicationListService.getAll();

    if(allApplicationLists.empty()) ui->title->setText("Create your first application list");

    for (const sun::persistence::ApplicationList& list : allApplicationLists) {
        if(!list.name.has_value() || list.name->isEmpty()) continue;
        insertApplicationList(list);
    }
}

void ApplicationDialog::insertApplicationList(const sun::persistence::ApplicationList& list)
{
    QTreeWidgetItem* listItem = new QTreeWidgetItem(ui->applicationTree);

    listItem->setText(0, *list.name);
    listItem->setFlags(listItem->flags() | Qt::ItemIsUserCheckable);
    listItem->setCheckState(0, Qt::Unchecked);
    listItem->setData(0, ItemTypeRole, ListItemType);
    listItem->setData(0, ListIdRole, list.id);

    const QList<sun::persistence::Application> applications = applicationListService.getAllApplications(list.id);
    for (const sun::persistence::Application& application : applications) {
        QTreeWidgetItem* applicationItem = new QTreeWidgetItem(listItem);

        applicationItem->setText(0, application.name);
        applicationItem->setFlags(applicationItem->flags() | Qt::ItemIsUserCheckable);
        applicationItem->setCheckState(0, Qt::Unchecked);

        applicationItem->setData(0, ItemTypeRole, ApplicationItemType);
        applicationItem->setData(0, ListIdRole, list.id);
        applicationItem->setData(0, ApplicationIdRole, application.id);
    }

    listItem->setExpanded(false);
}

void ApplicationDialog::onItemChanged(QTreeWidgetItem* item, int column)
{
    if (column != 0) return;

    QSignalBlocker blocker(ui->applicationTree);

    const int itemType = item->data(0, ItemTypeRole).toInt();

    if (itemType == ListItemType) {
        const Qt::CheckState state = item->checkState(0);

        for (int i = 0; i < item->childCount(); ++i) {
            item->child(i)->setCheckState(0, state);
        }

        return;
    }

    QTreeWidgetItem* parent = item->parent();

    if (!parent) {
        return;
    }

    int checkedCount = 0;

    for (int i = 0; i < parent->childCount(); ++i) {
        if (parent->child(i)->checkState(0) == Qt::Checked) {
            ++checkedCount;
        }
    }

    if (checkedCount == 0) {
        parent->setCheckState(0, Qt::Unchecked);
    } else if (checkedCount == parent->childCount()) {
        parent->setCheckState(0, Qt::Checked);
    } else {
        parent->setCheckState(0, Qt::PartiallyChecked);
    }
}

void ApplicationDialog::setApplicationLists(const QList<sun::persistence::ApplicationList>& applicationLists)
{
    QSignalBlocker blocker(ui->applicationTree);

    for (int i = 0; i < ui->applicationTree->topLevelItemCount(); ++i) {
        QTreeWidgetItem* listItem = ui->applicationTree->topLevelItem(i);

        listItem->setCheckState(0, Qt::Unchecked);

        for (int j = 0; j < listItem->childCount(); ++j) {
            listItem->child(j)->setCheckState(0, Qt::Unchecked);
        }
    }

    for (const sun::persistence::ApplicationList& selectedList : applicationLists) {
        if (selectedList.name.has_value()) {
            for (int i = 0; i < ui->applicationTree->topLevelItemCount(); ++i) {
                QTreeWidgetItem* listItem = ui->applicationTree->topLevelItem(i);
                const int listId = listItem->data(0, ListIdRole).toInt();

                if (selectedList.id != listId) continue;

                listItem->setCheckState(0, Qt::Checked);
                for (int j = 0; j < listItem->childCount(); ++j) {
                    listItem->child(j)->setCheckState(0, Qt::Checked);
                }
                break;
            }         
        } else {
            const QList<sun::persistence::Application> applications = applicationListService.getAllApplications(selectedList.id);
            for (int i = 0; i < ui->applicationTree->topLevelItemCount(); ++i) {
                QTreeWidgetItem* listItem = ui->applicationTree->topLevelItem(i);
                for (int j = 0; j < listItem->childCount(); ++j) {
                    QTreeWidgetItem* applicationItem = listItem->child(j);
                    const int applicationId = applicationItem->data(0, ApplicationIdRole).toInt();
                    for (const sun::persistence::Application& application : applications) {
                        if (application.id == applicationId) {
                            applicationItem->setCheckState(0, Qt::Checked);
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < ui->applicationTree->topLevelItemCount(); ++i) {
        QTreeWidgetItem* listItem = ui->applicationTree->topLevelItem(i);
        int checkedCount = 0;
        for (int j = 0; j < listItem->childCount(); ++j) {
            if (listItem->child(j)->checkState(0) == Qt::Checked) {
                ++checkedCount;
            }
        }

        if (checkedCount == 0) {
            listItem->setCheckState(0, Qt::Unchecked);
        } else if (checkedCount == listItem->childCount()) {
            listItem->setCheckState(0, Qt::Checked);
        } else {
            listItem->setCheckState(0, Qt::PartiallyChecked);
        }
    }
}

QList<sun::persistence::ApplicationList> ApplicationDialog::getSelectedApplicationListsIds() const
{
    QList<sun::persistence::ApplicationList> selectedLists;
    QList<int> selectedAppsIds;

    for (int i = 0; i < ui->applicationTree->topLevelItemCount(); ++i) {
        QTreeWidgetItem* listItem = ui->applicationTree->topLevelItem(i);

        const Qt::CheckState listState = listItem->checkState(0);

        if (listState == Qt::Unchecked) {
            continue;
        } else if (listState == Qt::Checked) {
            sun::persistence::ApplicationList applicationList;
            applicationList.id = listItem->data(0, ListIdRole).toInt();
            applicationList.name = listItem->text(0);
            selectedLists.append(applicationList);
        } else {
             for (int j = 0; j < listItem->childCount(); ++j) {
                QTreeWidgetItem* applicationItem = listItem->child(j);

                const Qt::CheckState applicationState = listItem->checkState(0);

                if (listState == Qt::Unchecked) {
                    continue;
                 } else {
                    selectedAppsIds.append(applicationItem->data(0, ApplicationIdRole).toInt());
                 }
             }
        }
    }

    if(!selectedAppsIds.empty()) {
        sun::persistence::CreateApplicationListDto createApplicationListDto;
        createApplicationListDto.name = std::nullopt;
        sun::persistence::ApplicationList namelessList = applicationListService.create(createApplicationListDto);
        
        for(int appId : selectedAppsIds) {
            applicationListService.addApplication(namelessList.id, appId);
        }
        selectedLists.append(namelessList);
    }

    return selectedLists;
}