#include "mainwindow.h"
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QRectF>

MainWindow::MainWindow(QWidget *parent) :
    QGraphicsView(parent)
{
  view = new QWebEngineView();
  scene = new QGraphicsScene(this);
  viewProxy = scene->addWidget(view);
  setScene(scene);

  QFile file("../helloworld.html");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  QTextStream in (&file);
  html = in.readAll();
  view->setHtml(html, QUrl::fromLocalFile("/home/laura/programming/life-verse/"));
  // view->load(QUrl("http://localhost:3000/helloworld.html"));
}

MainWindow::~MainWindow()
{
  delete view;
  QCoreApplication::quit();
}

void
MainWindow::resizeEvent(QResizeEvent* e) {
  viewProxy->setGeometry(QRectF(viewport()->rect()));
}

void
MainWindow::closeEvent(QCloseEvent* e) {
  QCoreApplication::quit();
}
