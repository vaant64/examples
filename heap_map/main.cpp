#include "qpaintwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPaintWidget w;
    w.show();
    return a.exec();
}
