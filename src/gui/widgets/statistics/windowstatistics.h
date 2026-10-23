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

    QString getProgramIconPath() const;
    void setProgramIconPath(const QString& path);

    QString getWorkTime() const;
    void setWorkTime(const QString& time);

    QString getWorkTimeIconPath() const;
    void setWorkTimeIconPath(const QString& path);

    QString getStatus() const;
    void setStatus(const QString& stat);

private:
    Ui::WindowStatistics *ui;

    QString programName;
    QString programIconPath;
    QString workTime;
    QString workTimeIconPath;
    QString status;
};

#endif // WINDOWSTATISTICS_H