/********************************************************************************
** Form generated from reading UI file 'mywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWIDGET_H
#define UI_MYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myWidget
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_s;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit_d;
    QPushButton *pushButtonExit;
    QPushButton *pushButtonStart;

    void setupUi(QWidget *myWidget)
    {
        if (myWidget->objectName().isEmpty())
            myWidget->setObjectName(QString::fromUtf8("myWidget"));
        myWidget->resize(743, 414);
        label = new QLabel(myWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 50, 661, 41));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        label_2 = new QLabel(myWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 90, 661, 41));
        label_2->setFont(font);
        lineEdit_s = new QLineEdit(myWidget);
        lineEdit_s->setObjectName(QString::fromUtf8("lineEdit_s"));
        lineEdit_s->setGeometry(QRect(190, 170, 481, 41));
        QFont font1;
        font1.setPointSize(13);
        lineEdit_s->setFont(font1);
        label_3 = new QLabel(myWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 180, 131, 20));
        label_3->setFont(font1);
        label_4 = new QLabel(myWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 250, 131, 20));
        label_4->setFont(font1);
        lineEdit_d = new QLineEdit(myWidget);
        lineEdit_d->setObjectName(QString::fromUtf8("lineEdit_d"));
        lineEdit_d->setGeometry(QRect(190, 240, 481, 41));
        lineEdit_d->setFont(font1);
        pushButtonExit = new QPushButton(myWidget);
        pushButtonExit->setObjectName(QString::fromUtf8("pushButtonExit"));
        pushButtonExit->setGeometry(QRect(390, 340, 94, 27));
        pushButtonStart = new QPushButton(myWidget);
        pushButtonStart->setObjectName(QString::fromUtf8("pushButtonStart"));
        pushButtonStart->setGeometry(QRect(250, 340, 94, 27));

        retranslateUi(myWidget);

        QMetaObject::connectSlotsByName(myWidget);
    } // setupUi

    void retranslateUi(QWidget *myWidget)
    {
        myWidget->setWindowTitle(QCoreApplication::translate("myWidget", "myWidget", nullptr));
        label->setText(QCoreApplication::translate("myWidget", "        Welcome! We will copy the source file to the destinaiton file with ", nullptr));
        label_2->setText(QCoreApplication::translate("myWidget", "3 sub-processes created and 2 buffers used. Please enter the pathes.", nullptr));
        lineEdit_s->setText(QString());
        label_3->setText(QCoreApplication::translate("myWidget", "source file path:", nullptr));
        label_4->setText(QCoreApplication::translate("myWidget", "destination path:", nullptr));
        lineEdit_d->setText(QString());
        pushButtonExit->setText(QCoreApplication::translate("myWidget", "EXIT", nullptr));
        pushButtonStart->setText(QCoreApplication::translate("myWidget", "START", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myWidget: public Ui_myWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWIDGET_H
