#include "mainwidget.h"
#include <QApplication>
#include "frmnum.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWidget w;
    w.show();
    //小键盘
    frmNum::Instance()->Init("black", 10);
    frmNum::Instance()->hide();
    return a.exec();
}
