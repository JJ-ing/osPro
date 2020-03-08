/********************************************************************************
** Form generated from reading UI file 'sub1widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUB1WIDGET_H
#define UI_SUB1WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sub1Widget
{
public:
    QProgressBar *progressBar;
    QLabel *label_2;
    QTextBrowser *textBrowser;
    QLabel *label;

    void setupUi(QWidget *sub1Widget)
    {
        if (sub1Widget->objectName().isEmpty())
            sub1Widget->setObjectName(QString::fromUtf8("sub1Widget"));
        sub1Widget->resize(403, 304);
        progressBar = new QProgressBar(sub1Widget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(30, 250, 341, 27));
        progressBar->setValue(24);
        label_2 = new QLabel(sub1Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(29, 39, 341, 20));
        textBrowser = new QTextBrowser(sub1Widget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(30, 70, 341, 166));
        label = new QLabel(sub1Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 341, 20));

        retranslateUi(sub1Widget);

        QMetaObject::connectSlotsByName(sub1Widget);
    } // setupUi

    void retranslateUi(QWidget *sub1Widget)
    {
        sub1Widget->setWindowTitle(QCoreApplication::translate("sub1Widget", "sub1Widget", nullptr));
        label_2->setText(QCoreApplication::translate("sub1Widget", "There are contents and process-bar below.", nullptr));
        label->setText(QCoreApplication::translate("sub1Widget", "      Copy characters from souce file to buffer A.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sub1Widget: public Ui_sub1Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUB1WIDGET_H
