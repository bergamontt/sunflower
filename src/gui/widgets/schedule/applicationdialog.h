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

    void setApplicationLists(const QList<sun::persistence::ApplicationList>& applicationLists);
    QList<sun::persistence::ApplicationList> getSelectedApplicationListsIds() const;

private slots:
    void onItemChanged(QTreeWidgetItem* item, int column);

private:
    Ui::ApplicationDialog *ui;
    sun::core::ApplicationListService applicationListService;

    void loadApplicationLists();
};

#endif // APPLICATIONDIALOG_H
