#include "widget.h"
#include "ui_widget.h"
#include "QTcpSocket"
#include "QTcpServer"
#include "QProcess"
#include "QString"
#include "QFile"
#include "QFileDialog"
#include "QMessageBox";
#include "QDebug"
QString Ip;
QFile file;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    socket=new QTcpSocket;
    server=new QTcpServer;
    server->listen(QHostAddress::Any,4567);

    connect(server,&QTcpServer::newConnection,this,&Widget::NewConnectionHandler);
    ui->setupUi(this);

}

Widget::~Widget()
{
    delete ui;

}
void Widget::readData()
{
    qDebug()<<"the widget is ready to read data";

        if (!file.isOpen()) {
            QString filePath = QFileDialog::getSaveFileName(nullptr, "Save File As");

            if (filePath.isEmpty()) {

                qDebug() << "No file selected";

                return;

            }

            file.setFileName(filePath);

            if (!file.open(QIODevice::WriteOnly)) {

                qDebug() << "Could not open file for writing";

                return;

            }

        }



        QByteArray data = socket->readAll();
        file.write(data);
        file.close();

    }







void Widget::NewConnectionHandler()
{
    QTcpSocket *s=(QTcpSocket *)server->nextPendingConnection();
    connect(s,&QTcpSocket::readyRead,this,&Widget::readData);
    qDebug()<<"new connection established";
    QMessageBox::information(this,"connected socket","Info");
    socket=s;
}

void Widget::on_pushButton_clicked()
{
    Ip=ui->IP->text();
     qDebug()<<"server opened";
    socket->connectToHost(QHostAddress(Ip),4567);
    connect(socket,&QTcpSocket::connected,[this]()
{
        connect(socket,&QTcpSocket::readyRead,this,&Widget::readData);

    });

}

