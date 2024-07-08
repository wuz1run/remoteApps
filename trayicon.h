#ifndef TRAYICON_H
#define TRAYICON_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QCoreApplication>
extern QStringList DriveList;
class trayIcon : public QMainWindow
{
    Q_OBJECT

public:
    explicit trayIcon(QWidget *parent = nullptr);

private:
    QSystemTrayIcon trayicon;
    QMenu *trayMenu;
    QAction *showAction;
    QAction *quitAction;


private slots:
    void showMainWindow();
    void quitApplication();
};

#endif // TRAYICON_H
