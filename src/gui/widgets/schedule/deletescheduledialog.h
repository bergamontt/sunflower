#ifndef DELETESCHEDULEDIALOG_H
#define DELETESCHEDULEDIALOG_H

#include <QDialog>

namespace Ui {
class DeleteScheduleDialog;
}

class DeleteScheduleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteScheduleDialog(QWidget *parent = nullptr);
    ~DeleteScheduleDialog();

    void setSchedule(QString scheduleName);

private:
    Ui::DeleteScheduleDialog *ui;
};

#endif // DELETESCHEDULEDIALOG_H
