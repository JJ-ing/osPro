#ifndef SUB3WIDGET_H
#define SUB3WIDGET_H

#include <QWidget>
#include "MyThread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class sub3Widget; }
QT_END_NAMESPACE

class sub3Widget : public QWidget
{
    Q_OBJECT

public:
    void to_emit_signal(int, char **);
    sub3Widget(QWidget *parent = nullptr);
    ~sub3Widget();

private:
    Ui::sub3Widget *ui;
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
#endif // SUB3WIDGET_H
