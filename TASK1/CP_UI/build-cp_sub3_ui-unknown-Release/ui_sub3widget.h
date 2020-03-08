/********************************************************************************
** Form generated from reading UI file 'sub3widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUB3WIDGET_H
#define UI_SUB3WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sub3Widget
{
public:
    QProgressBar *progressBar;
    QLabel *label_2;
    QLabel *label;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *sub3Widget)
    {
        if (sub3Widget->objectName().isEmpty())
            sub3Widget->setObjectName(QString::fromUtf8("sub3Widget"));
        sub3Widget->resize(401, 300);
        progressBar = new QProgressBar(sub3Widget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(30, 250, 341, 27));
        progressBar->setValue(24);
        label_2 = new QLabel(sub3Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(29, 39, 341, 20));
        label = new QLabel(sub3Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 351, 20));
        textBrowser = new QTextBrowser(sub3Widget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(30, 70, 341, 166));

        retranslateUi(sub3Widget);

        QMetaObject::connectSlotsByName(sub3Widget);
    } // setupUi

    void retranslateUi(QWidget *sub3Widget)
    {
        sub3Widget->setWindowTitle(QCoreApplication::translate("sub3Widget", "sub3Widget", nullptr));
        label_2->setText(QCoreApplication::translate("sub3Widget", "There are contents and process-bar below.", nullptr));
        label->setText(QCoreApplication::translate("sub3Widget", "     Copy characters from buffer B to destination.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sub3Widget: public Ui_sub3Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUB3WIDGET_H
