#ifndef BLOCKPAGE_H
#define BLOCKPAGE_H

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

#endif // BLOCKPAGE_H
