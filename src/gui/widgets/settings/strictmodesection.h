#ifndef STRICTMODESECTION_H
#define STRICTMODESECTION_H

#include <QFrame>

namespace Ui {
class StrictModeSection;
}

class StrictModeSection : public QFrame
{
    Q_OBJECT

public:
    explicit StrictModeSection(QWidget *parent = nullptr);
    ~StrictModeSection();

private:
    void updateSettingsSectionSize(int index);
    void updatePasswordSettings(bool hasPassword);

private:
    Ui::StrictModeSection *ui;
};

#endif // STRICTMODESECTION_H
