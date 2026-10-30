#ifndef PASSWORDCONFIRMATION_H
#define PASSWORDCONFIRMATION_H

#include <QDialog>

namespace Ui {
class PasswordConfirmation;
}

class PasswordConfirmation : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordConfirmation(QWidget *parent = nullptr);
    ~PasswordConfirmation();

private:
    Ui::PasswordConfirmation *ui;
};

#endif // PASSWORDCONFIRMATION_H
