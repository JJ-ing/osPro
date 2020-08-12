#ifndef SUB2WIDGET_H
#define SUB2WIDGET_H

#include <QWidget>
#include "MyThread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class sub2Widget; }
QT_END_NAMESPACE

class sub2Widget : public QWidget
{
    Q_OBJECT

public:
    void to_emit_signal(int, char **);
    sub2Widget(QWidget *parent = nullptr);
    ~sub2Widget();

private:
    Ui::sub2Widget *ui;
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
#endif // SUB2WIDGET_H
