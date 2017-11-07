#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
  view = new QWebEngineView(this);
  setCentralWidget(view);
}

MainWindow::~MainWindow()
{
}
