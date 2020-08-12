#include "sub1widget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sub1Widget w;
    w.show();
    w.to_emit_signal(argc, argv);
    return a.exec();
}

