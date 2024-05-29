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
    //创建Socket和Server对象
    server->listen(QHostAddress::Any,4567);
    //server监听任何QHostAddress和4567端口
    connect(server,&QTcpServer::newConnection,this,&Widget::NewConnectionHandler);
    //将Tcpserver的newConnection 信号与Widget里的NewConnectionHandler连接，让NewConnectionHandler来处理信号
    ui->setupUi(this);
   //Ui设置

}

Widget::~Widget()
{
    delete ui;

}
//析构函数
/**************************************
 * 下面我写了三个函数，void handleLnk();void handleExe();void rdpConnection();
 * 拿来处理lnk文件，exe文件（远程安装）还有连接--developed 5.29
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * *************************************/

void Widget::NewConnectionHandler()
{
    QTcpSocket *s=(QTcpSocket *)server->nextPendingConnection();
    //传递参数，形式参数s作为server连接中的对象
    connect(s,&QTcpSocket::readyRead,this,&Widget::readData);
    //s 作为发送的socket会发出readyRead信号，将其与readData函数连接。让readData来处理
    qDebug()<<"new connection established";
    //debug输出
    QMessageBox::information(this,"connected socket","Info");
    //弹框表明连接成功
    socket=s;
    //复制连接中的socket给另一个函数使用
}



void Widget::readData()
{
    qDebug()<<"the widget is ready to read data";
    //这就是readData函数，来处理传入的socket
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
    //QFileDialog选择存储路径，后期应该删除修改为固定路径
    QByteArray data = socket->readAll();
    //数据只能存在QByteArray中，使用传入socket的realAll方法读取
    file.write(data);
    //将data写到file中
    file.close();
    //解除占用

}

void Widget::on_pushButton_clicked()
{
    Ip=ui->IP->text();
     qDebug()<<"server opened";
    //获取输入的IP
    socket->connectToHost(QHostAddress(Ip),4567);
     //连接socket
}
void Widget::handleLnk()
{

}

void Widget::handleExe()
{

}

void Widget::rdpConnection()
{

}

