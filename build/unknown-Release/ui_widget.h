/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton;
    QLineEdit *User;
    QPushButton *pushButton_2;
    QLabel *label;
    QLineEdit *Pass;
    QLineEdit *IP;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(260, 430, 80, 26));
        User = new QLineEdit(Widget);
        User->setObjectName(QString::fromUtf8("User"));
        User->setGeometry(QRect(130, 90, 113, 21));
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(290, 160, 80, 20));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(280, 70, 41, 14));
        Pass = new QLineEdit(Widget);
        Pass->setObjectName(QString::fromUtf8("Pass"));
        Pass->setGeometry(QRect(280, 90, 113, 21));
        IP = new QLineEdit(Widget);
        IP->setObjectName(QString::fromUtf8("IP"));
        IP->setGeometry(QRect(430, 90, 113, 21));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(130, 70, 41, 14));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(430, 70, 41, 14));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "Connnet", nullptr));
        label->setText(QCoreApplication::translate("Widget", "Pass", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "User", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "IP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
