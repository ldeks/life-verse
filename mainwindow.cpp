#include "mainwindow.h"
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
  view = new QWebEngineView(this);
  setCentralWidget(view);

  QFile file("../helloworld.html");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  QTextStream in (&file);
  html = in.readAll();
  view->setHtml(html, QUrl::fromLocalFile("/home/laura/programming/life-verse/"));
  // view->load(QUrl("http://localhost:3000/helloworld.html"));
  view->show();
}

MainWindow::~MainWindow()
{
}
