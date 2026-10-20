#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>
#include <QMenu>
#include <QAction>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->navigationList,
        &QListWidget::currentRowChanged,
        ui->pageStack,
        &QStackedWidget::setCurrentIndex);

    QMenu* trayMenu = new QMenu(this);
    trayMenu->addAction("Open Sunflower", this, [this]
    {
        show();
        activateWindow();    
    });
    trayMenu->addSeparator();
    trayMenu->addAction("Quit Sunflower", qApp, &QCoreApplication::quit);

    QIcon icon(":gui/sunflower.svg");

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("Sunflower");
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    setWindowIcon(icon);

    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);

    setWindowTitle("SunFlower");
    resize(1024, 640);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (isVisible())
    {
        event->ignore();
        hide();
    }
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
        show();
        activateWindow();
        break;
    default:
        break;
    }
}