#ifndef APPLICATIONSDIALOG_H
#define APPLICATIONSDIALOG_H

#include "application/iapplicationservice.h"
#include "applicationlist/iapplicationlistservice.h"
#include "applicationlist.h"
#include <QDialog>

#include <memory>

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
    std::unique_ptr<sun::core::IApplicationService> applicationService;
    std::unique_ptr<sun::core::IApplicationListService> applicationListService;

    void loadApplications();
    void validateForm();
};

#endif // APPLICATIONSDIALOG_H
