#include "widget.h"
#include "ui_widget.h"
#include "QString"
#include "QProcess"
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
QString ss;
void Widget::on_pushButton_2_clicked()
{

    QProcess::execute(ss);
}

