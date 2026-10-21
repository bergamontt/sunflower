#ifndef SCHEDULEPAGE_H
#define SCHEDULEPAGE_H

#include <QWidget>

namespace Ui {
class SchedulePage;
}

class SchedulePage : public QWidget
{
    Q_OBJECT

public:
    explicit SchedulePage(QWidget *parent = nullptr);
    ~SchedulePage();

private:
    Ui::SchedulePage *ui;
};

#endif // SCHEDULEPAGE_H
