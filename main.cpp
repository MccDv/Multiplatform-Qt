#include "mvtest.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MvTest w;
    w.show();
    return a.exec();
}
