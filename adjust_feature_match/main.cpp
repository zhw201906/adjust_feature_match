#include "AutoAdjust.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AutoAdjust w;
    w.show();
    return a.exec();
}
