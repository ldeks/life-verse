#include "renderer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Renderer r;
    r.show();

    return a.exec();
}
