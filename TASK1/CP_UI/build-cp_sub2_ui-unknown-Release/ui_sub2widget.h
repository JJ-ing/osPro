/********************************************************************************
** Form generated from reading UI file 'sub2widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUB2WIDGET_H
#define UI_SUB2WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sub2Widget
{
public:
    QTextBrowser *textBrowser;
    QLabel *label;
    QLabel *label_2;
    QProgressBar *progressBar;

    void setupUi(QWidget *sub2Widget)
    {
        if (sub2Widget->objectName().isEmpty())
            sub2Widget->setObjectName(QString::fromUtf8("sub2Widget"));
        sub2Widget->resize(399, 302);
        textBrowser = new QTextBrowser(sub2Widget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(30, 70, 341, 166));
        label = new QLabel(sub2Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 341, 20));
        label_2 = new QLabel(sub2Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(29, 39, 341, 20));
        progressBar = new QProgressBar(sub2Widget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(30, 250, 341, 27));
        progressBar->setValue(24);

        retranslateUi(sub2Widget);

        QMetaObject::connectSlotsByName(sub2Widget);
    } // setupUi

    void retranslateUi(QWidget *sub2Widget)
    {
        sub2Widget->setWindowTitle(QCoreApplication::translate("sub2Widget", "sub2Widget", nullptr));
        label->setText(QCoreApplication::translate("sub2Widget", "      Copy characters from buffer A to buffer B.", nullptr));
        label_2->setText(QCoreApplication::translate("sub2Widget", "There are contents and process-bar below.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sub2Widget: public Ui_sub2Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUB2WIDGET_H
