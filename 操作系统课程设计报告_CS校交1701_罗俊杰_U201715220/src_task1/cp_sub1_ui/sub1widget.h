#ifndef SUB1WIDGET_H
#define SUB1WIDGET_H

#include <QWidget>
#include "MyThread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class sub1Widget; }
QT_END_NAMESPACE

class sub1Widget : public QWidget
{
    Q_OBJECT

public:
    sub1Widget(QWidget *parent = nullptr);
    ~sub1Widget();
    void to_emit_signal(int, char **);

private:
    Ui::sub1Widget *ui;
    MyThread *mythread;


private slots:
//    void _dealFile(int argc, char **argv);
    void _dealfileSize(int);
    void _dealcopySum(int);
    void _dealcopyContents(QString);
    void _dealover(void);
//    void _dealdestroy(void);

signals:
    void _start(int, char**);

};
#endif // SUB1WIDGET_H
