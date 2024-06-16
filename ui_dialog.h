/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *Usernamer;
    QLineEdit *Passworder;
    QLabel *Username;
    QLabel *label;
    ~Ui_Dialog();
    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        Usernamer = new QLineEdit(Dialog);
        Usernamer->setObjectName(QStringLiteral("Usernamer"));
        Usernamer->setGeometry(QRect(110, 90, 113, 21));
        Passworder = new QLineEdit(Dialog);
        Passworder->setObjectName(QStringLiteral("Passworder"));
        Passworder->setGeometry(QRect(110, 130, 113, 21));
        Username = new QLabel(Dialog);
        Username->setObjectName(QStringLiteral("Username"));
        Username->setGeometry(QRect(110, 70, 61, 16));
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(110, 110, 61, 16));

        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        Username->setText(QApplication::translate("Dialog", "UserName", nullptr));
        label->setText(QApplication::translate("Dialog", "Password", nullptr));
    } // retranslateUi

};

namespace Ui {
class Dialog: public Ui_Dialog {private slots:
};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
