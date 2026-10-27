#ifndef WINDOWSTATISTICS_H
#define WINDOWSTATISTICS_H

#include <QWidget>
#include <QString>

namespace Ui {
    class WindowStatistics;
}

class WindowStatistics : public QWidget
{
    Q_OBJECT

public:
    explicit WindowStatistics(QWidget *parent = nullptr);
    ~WindowStatistics();

    QString getProgramName() const;
    void setProgramName(const QString& name);

    QIcon getProgramIcon() const;
    void setProgramIcon(const QIcon& icon);

    QString getWorkTime() const;
    void setWorkTime(const QString& time);

    QString getWorkTimeIconPath() const;
    void setWorkTimeIconPath(const QString& path);

    QString getTimeLeft() const;
    void setTimeLeft(const QString& time);

private:
    Ui::WindowStatistics *ui;

    QString programName;
    QIcon programIcon;
    QString workTime;
    QString workTimeIconPath;
    QString timeLeft;
};

#endif // WINDOWSTATISTICS_H