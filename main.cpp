#include "renderer.h"
#include "mainwindow.h"
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Renderer r;
    r.show();

    MainWindow m;
    m.setMainRenderer(&r);
    m.show();

    QObject::connect(&m, &MainWindow::syncHtml, &r, &Renderer::setHtml);

    return a.exec();
}
