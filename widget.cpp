#include "widget.h"
#include "ui_widget.h"
#include "QTcpSocket"
#include "QTcpServer"
#include "QProcess"
#include "QString"
#include "QFile"
#include "QFileDialog"
#include "QMessageBox"
#include "QDebug"
QString Ip;
QString UsernamE;
QString Password;
QFile file;

QString LnkInLinux;
QString ExeInLinux;

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
Ui_Dialog::~Ui_Dialog()
{
    UsernamE=Usernamer->text();
    Password=Passworder->text();
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

bool Widget::createFolder(const QString &filePath)
{
    QDir dir;
    if(!dir.exists(filePath))
    {
        if(dir.mkpath(filePath))
        {
            qDebug()<<"Folder created successfully at"<<filePath;
            return true;
        }else{
            qDebug()<<"Failed to create folder at"<<filePath;
            return false;
        }
    }else{
        return true;
    }
}//创建文件夹,用来储存windows传来的lnk

void Widget::readData()
{
    qDebug()<<"the widget is ready to read data";
    //这就是readData函数，来处理传入的socket

    QTcpSocket *clientSocket = qobject_cast <QTcpSocket*>(sender());

    if(!clientSocket){
        return;
    }

    if(!file.isOpen()){
        file.setFileName("received_file.lnk");
        if(!file.open(QIODevice::WriteOnly)){
            qDebug()<<"Failed to open file for writing";
            return;
        }
    }

    QByteArray data = clientSocket->readAll();
    file.write(data);

}//处理传入的文件

void Widget::on_pushButton_clicked()
{
    Ip=ui->IP->text();
    qDebug()<<"server opened";
    //获取输入的IP
    socket->connectToHost(QHostAddress(Ip),4567);
    //连接socket
}
/*
 * 以上是TCP相关的代码
 *
 *
 *
 */
void Widget::openedFile(const QString &File)
{
    QFileInfo fileTemp(File);
    QString extend=fileTemp.suffix();
    if(extend=="lnk")
    {
        handleLnk(File);
    }
    else if(extend=="exe")
    {
        handleExe(File);
    }

}
void Widget::handleLnk(const QString &File)
{
    QString ans=parseLink(File);
    QMessageBox::warning(this,"lnk",ans);
    buildCommand(Ip,ans,UsernamE,Password);
}

void Widget::handleExe(const QString &File)
{
    QMessageBox::warning(this,"exe",File);
    QString ans=parseLink(File);
    QFile ExeFile(File);
    QByteArray FileArray=ExeFile.readAll();
    socket->write(FileArray);
    socket->flush();
    QMessageBox::warning(this,"sent executable",File);
    buildCommand(Ip,ans,UsernamE,Password);

}
/*以上是处理图形化界面/终端的代码
 *
 *
 *
 *
 */

bool Widget::isLnkFile(const QByteArray &link) {
    return link[0x00] == 0x4C;  // 76, 'L', 0x4C代表lnk文件格式
}

int Widget::bytes2short(const QByteArray &bytes, int off) {
    return static_cast<unsigned char>(bytes[off]) | (static_cast<unsigned char>(bytes[off + 1]) << 8);
}

QString Widget::getNullDelimitedString(const QByteArray &bytes, int off) {
    int len = 0;
    while (bytes[off + len] != '\0') {
        len++;
    }
    return QString::fromUtf8(bytes.mid(off, len));
}

QString Widget::parseLink(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("File not found");
    }

    QByteArray link = file.readAll();
    file.close();

    if (!isLnkFile(link)) {
        qDebug() << "Not a .lnk file";
        return "1111";
    }

    unsigned char flags = link[0x14];

    int shell_len = 0;
    if (flags & 0x1) {  // 判断是否包含shell item id list段
        shell_len = bytes2short(link, 0x4C) + 2;  // 获取shell item id list段的总长度，加2是为了将link[0x4c]本身的长度计算在内
    }

    int file_start = 0x4C + shell_len;
    int local_sys_off = static_cast<unsigned char>(link[file_start + 0x10]) + file_start;

    QString real_file = getNullDelimitedString(link, local_sys_off);
    qDebug() << "Real file path:" << real_file;
    return real_file;
}
/*
 *
 *
 *
 * 以上是解析lnk的代码
 *
 *
 *
 */
void Widget::on_TestButton_clicked()
{
    QString testLnkPath= QFileDialog::getOpenFileName(nullptr,"choose file");
    QString ans=parseLink(testLnkPath);
    QMessageBox::warning(this,"test",ans);
    Ip=ui->IP->text();
    QString username=UsernamE;
    QString password=Password;
    QString command=buildCommand(Ip,ans,username,password);
    QList <QString>commands;
    commands.append(command);
    qDebug()<<command;
    QProcess process;
    process.startDetached(command);
}
QString Widget::buildCommand(const QString &ip, const QString &filePath, const QString &username, const QString &password) {
    // 使用QString::arg()来构建命令字符串
    QString command = QString("xfreerdp /v:%1 /u:%2 /p:%3 /app:\"%4\"")
                          .arg(ip)
                          .arg(username)
                          .arg(password)
                          .arg(filePath);
    qDebug()<<command;
    ui->textEdit->setText(command);
    return command;
}

void Widget::rdpConnection()
{

}
/*
 *
 *
 *
 * 以上是处理ip和rdp连接的代码，process的代码最后要移动到rdpConnection之中
 *
 *
 */


void Widget::on_OpenSettings_clicked()
{
    openDialog();
}

void Widget::openDialog()
{
    QDialog dialogue(nullptr);
    Ui_Dialog dialog;
    dialog.setupUi(&dialogue);
    dialog.Usernamer->setText(UsernamE);
    dialog.Passworder->setText(Password);
    dialogue.exec();

}

