#include "trayicon.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCoreApplication>
#include <QTableWidget>
#include <QStorageInfo>
#include <QDebug>
#include <widget.h>
#include "QMessageBox"

trayIcon::trayIcon(QWidget *parent)
    : QMainWindow(parent),

    trayicon(this),
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
    for(QString ss:DriveList)
    QMessageBox::warning(nullptr,"111",ss);
}

void trayIcon::showMainWindow()
{
    QStringList list=DriveList;
    int argc=DriveList.size();
    int totalSize = 0;
    for (const QString &str : DriveList) {
        totalSize += str.length() + 1; // 加1是为了包括字符串结尾的空字符'\0'
    }
    char *argv = new char[totalSize];
    memset(argv, '\0', totalSize);
    int currentIndex = 0;
    for (const QString &str : DriveList) {
        strcpy(argv + currentIndex, str.toStdString().c_str());
        currentIndex += str.length() + 1; // 更新索引位置，跳过当前字符串的长度和空字符
    }
    for (int i = 0; i < totalSize; ++i) {
        if (argv[i] == '\0') {
            qDebug() << ""; // 输出换行符以分隔不同的字符串
        } else {
            qDebug() << argv[i]; // 输出字符
        }
    }
    delete[] argv;

    QTableWidget table;
    table.setColumnCount(2);
    table.setHorizontalHeaderLabels(QStringList() << "Drive" << "Select" );
    QList<QStorageInfo> allDrives = QStorageInfo::mountedVolumes();

    if (allDrives.size() != argc) {
        // 处理list和allDrives大小不匹配的情况
        return;
    }
    table.setRowCount(allDrives.size());
    for (int i = 0; i < allDrives.size(); ++i)
    {
        QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
        checkBoxItem->setCheckState(Qt::Unchecked); // 默认设置为未选中状态
        table.setItem(i, 1, checkBoxItem); // 设置复选框单元格
        table.setItem(i, 0, new QTableWidgetItem(DriveList[i]));
    }
    table.show();
    this->show();
}

void trayIcon::quitApplication()
{
    this->close();
}
