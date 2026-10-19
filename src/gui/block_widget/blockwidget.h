#ifndef BLOCKWIDGET_H
#define BLOCKWIDGET_H

#include <QWidget>

namespace Ui {
class BlockWidget;
}

class BlockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BlockWidget(QWidget *parent = nullptr);
    ~BlockWidget();

private:
    Ui::BlockWidget *ui;
};

#endif // BLOCKWIDGET_H
