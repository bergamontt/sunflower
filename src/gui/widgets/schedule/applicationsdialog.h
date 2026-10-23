#ifndef APPLICATIONSDIALOG_H
#define APPLICATIONSDIALOG_H

#include "application/applicationservice.h"
#include "applicationlist/applicationlistservice.h"
#include "applicationlist.h"
#include <QDialog>

namespace Ui {
class ApplicationsDialog;
}

class ApplicationsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ApplicationsDialog(QWidget *parent = nullptr);
    ~ApplicationsDialog();

    sun::persistence::ApplicationList getApplicationList() const;

private:
    Ui::ApplicationsDialog *ui;
    sun::core::ApplicationService applicationService;
    sun::core::ApplicationListService applicationListService;

    void loadApplications();
};

#endif // APPLICATIONSDIALOG_H
