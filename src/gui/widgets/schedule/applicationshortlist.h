#ifndef APPLICATIONSHORTLIST_H
#define APPLICATIONSHORTLIST_H

#include <QWidget>

namespace Ui {
class ApplicationShortList;
}

class ApplicationShortList : public QWidget
{
    Q_OBJECT

public:
    explicit ApplicationShortList(QWidget *parent = nullptr);
    ~ApplicationShortList();

private:
    Ui::ApplicationShortList *ui;
};

#endif // APPLICATIONSHORTLIST_H
