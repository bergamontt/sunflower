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

    sun::persistence::ApplicationList getNewApplicationList() const;
    sun::persistence::ApplicationList getEditedApplicationList() const;
    void setApplicationList(const sun::persistence::ApplicationList& applicationList);

private:
    Ui::ApplicationsDialog *ui;
    sun::core::ApplicationService applicationService;
    sun::core::ApplicationListService applicationListService;

    void loadApplications();
    void validateForm();
};

#endif // APPLICATIONSDIALOG_H
