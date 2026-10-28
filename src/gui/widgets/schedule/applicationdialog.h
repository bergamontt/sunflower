#ifndef APPLICATIONDIALOG_H
#define APPLICATIONDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

#include "applicationlist/applicationlistservice.h"

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
    sun::core::ApplicationListService applicationListService;

    void loadAllApplicationLists();
    void insertApplicationList(const sun::persistence::ApplicationList& list);
    void validateForm();
};

#endif // APPLICATIONDIALOG_H
