#include "widget.h"
#include "ui_widget.h"
#include "QTcpSocket"
#include "QTcpServer"
#include "QProcess"
#include "QString"
QString Ip;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;

}


void Widget::on_pushButton_clicked()
{
    Ip=ui->IP->text();

}

