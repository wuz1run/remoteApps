#include "trayicon.h"
#include <QMessageBox>

trayIcon::trayIcon(QWidget *parent)
    : QMainWindow(parent),
    trayMenu(new QMenu(this)),
    showAction(new QAction("USB Device Control", this)),
    quitAction(new QAction("Quit USB Control", this))
{
    trayicon.setToolTip("This is a demo of tooltip");
    trayicon.setIcon(QIcon("/usr/share/RemoteAPPs/resourses/icon.png")); // Use the resource path

    // Set up the tray menu
    trayMenu->addAction(showAction);
    trayMenu->addAction(quitAction);

    // Connect actions
    connect(showAction, &QAction::triggered, this, &trayIcon::showMainWindow);
    connect(quitAction, &QAction::triggered, this, &trayIcon::quitApplication);

    trayicon.setContextMenu(trayMenu);

    connect(&trayicon, &QSystemTrayIcon::activated, [](QSystemTrayIcon::ActivationReason reason){
        if(reason == QSystemTrayIcon::DoubleClick)
        {
            QMessageBox::information(nullptr, "Tray Icon", "Tray icon was double-clicked");
        }
        else if (reason == QSystemTrayIcon::Context)
        {
            // Handle right-click context menu if needed
        }
    });

    trayicon.show();
}

void trayIcon::showMainWindow()
{
    this->show();
}

void trayIcon::quitApplication()
{
    this->destroy();
}
