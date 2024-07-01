#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "QTcpSocket"
#include "QTcpServer"
#include "QProcess"
#include "QDebug"
#include "ui_dialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
     void openedFile(const QString &File);
    QString getDesktopPath();
    QString buildDriveCommand(const QString &ip, const QString &drivesymbol, const QString &username, const QString &password);

private slots:
    void on_pushButton_clicked();
    void readData();
    void NewConnectionHandler();
    void handleLnk(const QString &File);
    void handleExe(const QString &File);
    void rdpConnection();
    bool createFolder(const QString &filePath);
    bool isLnkFile(const QByteArray &link);
    int bytes2short(const QByteArray &bytes, int off);
    QString getNullDelimitedString(const QByteArray &bytes, int off);
    QString parseLink(const QString &filePath);
    QString buildCommand(const QString &ip, const QString &filePath, const QString &username, const QString &password);

    void on_TestButton_clicked();
    void handleDrive();

    void on_OpenSettings_clicked();
    void openDialog();
    void readconfig();
    QString getIp();
    QStringList readData2();
    void NewConnectionHandler2();
private:
    Ui::Widget *ui;
    QTcpSocket *socket;
    QTcpServer *server;
    Ui_Dialog dialog;
    QTcpServer *server2;

};
#endif // WIDGET_H
