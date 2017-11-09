#include "mainwindow.h"
#include <QCoreApplication>
#include <QFile>
#include <QIcon>
#include <QTextStream>
#include <QRectF>
#include <QString>

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

  toolbar = new QFrame();
  toolbarLayout = new QHBoxLayout(toolbar);
  bold = new QAction(QIcon("../bold.png"), "&Bold", toolbar);
  boldButton = new QToolButton(toolbar);
  boldButton->setDefaultAction(bold);
  boldButton->setAutoRaise(true);
  italic = new QAction(QIcon("../italic.png"), "&Italic", toolbar);
  italicButton = new QToolButton(toolbar);
  italicButton->setDefaultAction(italic);
  italicButton->setAutoRaise(true);
  toolbarLayout->addWidget(boldButton);
  toolbarLayout->addWidget(italicButton);
  toolbar->setLayout(toolbarLayout);

  toolbar->setWindowOpacity(0.7);
  QString css;
  css += "QFrame { background: dark-gray }";
  css += "QToolButton:hover { background: DimGray }";
  toolbar->setStyleSheet(css);
  toolbarProxy = scene->addWidget(toolbar);
  positionToolbar();
}

MainWindow::~MainWindow()
{
  delete view;
  delete toolbar;
  QCoreApplication::quit();
}

void
MainWindow::resizeEvent(QResizeEvent* e) {
  viewProxy->setGeometry(QRectF(viewport()->rect()));
  positionToolbar();
}

void
MainWindow::closeEvent(QCloseEvent* e) {
  QCoreApplication::quit();
}

void
MainWindow::positionToolbar() {
    int width = viewport()->width();
    int height = viewport()->height();
    toolbarProxy->setPos(0.10*width, 0.85*height);
}
