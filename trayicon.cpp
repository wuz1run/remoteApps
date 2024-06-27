#include "trayicon.h"

trayIcon::trayIcon(QWidget *parent)
    : QMainWindow{parent}

{
    trayicon.setToolTip("this is a demo of tooltip");
    trayicon.setIcon(QIcon("/resourse/icon.png"));
    connect(&trayicon,&QSystemTrayIcon::activated,[](QSystemTrayIcon::ActivationReason reason){
        if(reason == QSystemTrayIcon::DoubleClick)
            {

        }
        else if (reason == QSystemTrayIcon::Context)
            {

            }
    });
}

