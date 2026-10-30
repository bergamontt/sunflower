#ifndef APPLICATIONDIALOG_H
#define APPLICATIONDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

#include <memory>

#include "applicationlist.h"
#include "applicationlist/iapplicationlistservice.h"
#include "schedule/ischeduledservice.h"

namespace Ui {
class ApplicationDialog;
}

class ApplicationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ApplicationDialog(QWidget *parent = nullptr);
    ~ApplicationDialog();

    void setSelectedApplicationLists(const QList<sun::persistence::ApplicationList>& applicationLists);
    QList<sun::persistence::ApplicationList> getSelectedApplicationLists() const;

private slots:
    void onNewListButtonClicked();

private:
    Ui::ApplicationDialog *ui;
    std::unique_ptr<sun::core::IApplicationListService> applicationListService;
    std::unique_ptr<sun::core::IScheduleService> scheduleService;


    void loadAllApplicationLists();
    void insertApplicationList(const sun::persistence::ApplicationList& list);
    void validateForm();

    void setUpAppListButtons(QTreeWidgetItem* listItem, const sun::persistence::ApplicationList& list);
    void onEditButtonClicked(const sun::persistence::ApplicationList& applicationList);
    void onDeleteButtonClicked(int listId, QString listName);
    void removeApplicationListItemById(int id);
};

#endif // APPLICATIONDIALOG_H
