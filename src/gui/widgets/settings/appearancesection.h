#ifndef APPEARANCESECTION_H
#define APPEARANCESECTION_H

#include <QFrame>

namespace Ui {
class AppearanceSection;
}

class AppearanceSection : public QFrame
{
    Q_OBJECT

public:
    explicit AppearanceSection(QWidget *parent = nullptr);
    ~AppearanceSection();

private:
    Ui::AppearanceSection *ui;
};

#endif // APPEARANCESECTION_H
