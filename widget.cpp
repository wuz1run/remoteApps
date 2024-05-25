#include "widget.h"
#include "ui_widget.h"
#include "QTcpSocket"
#include "QTcpServer"
#include "QProcess"
#include "QString"
QString Ip;
QTcpSocket socket;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    socket=new QTcpSocket;
    server=new QTcpServer;
}

Widget::~Widget()
{
    delete ui;

}
void Widget::readData()
{
    QTcpSocket *s=(QTcpSocket *) sender();


}

void Widget::on_pushButton_clicked()
{
    Ip=ui->IP->text();
    socket->connectToHost(QHostAddress(Ip),4567);
    connect(socket,&QTcpSocket::connected,[this]()
{
        connect(socket,&QTcpSocket::readyRead,this,&Widget::readData);

    });
}

