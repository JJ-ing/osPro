#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class myWidget; }
QT_END_NAMESPACE

class myWidget : public QWidget
{
    Q_OBJECT

public:
    myWidget(QWidget *parent = nullptr);
    ~myWidget();

private slots:
    void on_pushButtonStart_clicked();

    void on_pushButtonExit_clicked();

private:
    Ui::myWidget *ui;
    // windows of 3 sub-processes
//    subwidget1 sub1;
//    subwidget2 sub2;
//    subwidget3 sub3;
};
#endif // MYWIDGET_H
