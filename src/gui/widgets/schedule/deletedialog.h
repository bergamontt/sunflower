#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>

namespace Ui {
class DeleteDialog;
}

class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteDialog(QWidget *parent = nullptr);
    ~DeleteDialog();

    void setItem(QString mame);

private:
    Ui::DeleteDialog *ui;
};

#endif // DELETESCHEDULEDIALOG_H
