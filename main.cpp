#include "renderer.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Renderer r;
    r.show();

    MainWindow m;
    m.show();

    return a.exec();
}
