#include "cam_control.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Cam_control w;
    w.show();

    return a.exec();
}
