#ifndef TRAYICON_H
#define TRAYICON_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QWidget>
#include "widget.h"
class trayIcon : public QMainWindow
{
    Q_OBJECT
public:
    trayIcon(QWidget *parent = nullptr);
    void setTrayicon(const QSystemTrayIcon &newTrayicon);

private:
    QSystemTrayIcon trayicon;



signals:
};

#endif // TRAYICON_H
