#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "QTcpSocket"
#include "QTcpServer"
#include "QProcess"
#include "QDebug"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void readData();
    void NewConnectionHandler();
    void handleLnk();
    void handleExe();
    void rdpConnection();

private:
    Ui::Widget *ui;
    QTcpSocket *socket;
    QTcpServer *server;
};
#endif // WIDGET_H
