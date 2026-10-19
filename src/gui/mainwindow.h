#pragma once

#include <QMainWindow>
#include <QSystemTrayIcon>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    QSystemTrayIcon* trayIcon;
};