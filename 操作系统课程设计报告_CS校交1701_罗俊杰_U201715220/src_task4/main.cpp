#include "manwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ManWidget w;
    w.show();
    return a.exec();
}

