#ifndef BLOCKPAGE_H
#define BLOCKPAGE_H

#include <QWidget>

namespace Ui {
class BlockPage;
}

class BlockPage : public QWidget
{
    Q_OBJECT

public:
    explicit BlockPage(QWidget *parent = nullptr);
    ~BlockPage();

private:
    Ui::BlockPage *ui;
};

#endif // BLOCKPAGE_H
