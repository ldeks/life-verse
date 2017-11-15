#include "mainwindow.h"
#include <QCoreApplication>
#include <QFile>
#include <QIcon>
#include <QTextStream>
#include <QRectF>
#include <QString>
#include <QStringList>

#include "deck.h"

MainWindow::MainWindow(QWidget *parent) :
    QGraphicsView(parent)
{
  // Renderer setup.
  view = new QWebEngineView();
  scene = new QGraphicsScene(this);
  viewProxy = scene->addWidget(view);
  setScene(scene);
  setMouseTracking(true);

  QFile file("../helloworld.html");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  QTextStream in (&file);
  html = in.readAll();
  view->setHtml(html, QUrl::fromLocalFile("/home/laura/programming/life-verse/"));
  // view->load(QUrl("http://localhost:3000/helloworld.html"));

  // Toolbar setup.
  toolbar = new DarkPopupWidget();
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
  fontCombo = new QFontComboBox(toolbar);
  toolbarLayout->addWidget(fontCombo);
  toolbar->setLayout(toolbarLayout);

  toolbar->addCSS("QToolButton:hover { background: DimGray }");
  toolbar->addToScene(scene);
  toolbar->setPositionWeights(0.10, 0.05);
  toolbar->setXPadding(100);
  toolbar->setYPadding(300);
  toolbar->updatePosition(viewport()->width(), viewport()->height());

  // List setup.
  listWidget = new DarkPopupWidget();
  listLayout = new QVBoxLayout(listWidget);
  listView = new QListView(listWidget);
  listView->setResizeMode(QListView::Adjust);
  listView->setLayoutMode(QListView::Batched);
  listModel = new QStringListModel(listWidget);
  QStringList serviceItems;
  serviceItems << "Praise to the Lord" << "Greater" << "Good Good Father" <<
    "Praise the King" << "Children's Dismissal" <<
    "Making Wise Decisions: Faith in Action - Rahab" <<  "Blessed Assurance";
  listModel->setStringList(serviceItems);
  listView->setModel(listModel);
  listLayout->addWidget(listView);
  listWidget->setLayout(listLayout);

  listWidget->addToScene(scene);
  listWidget->setMinimumSize(200, 400);
  listWidget->setPositionWeights(0.02, 0.3);
  listWidget->updatePosition(viewport()->width(), viewport()->height());

  Deck out;
  out.writeFile();
}

MainWindow::~MainWindow()
{
  delete view;
  delete toolbar;
  delete listWidget;
  QCoreApplication::quit();
}

void
MainWindow::resizeEvent(QResizeEvent* e) {
  viewProxy->setGeometry(QRectF(viewport()->rect()));
  toolbar->updatePosition(viewport()->width(), viewport()->height());
  listWidget->updatePosition(viewport()->width(), viewport()->height());
}

void
MainWindow::closeEvent(QCloseEvent* e) {
  QCoreApplication::quit();
}

void
MainWindow::mouseMoveEvent(QMouseEvent* e) {
  int xLoc = e->pos().x();
  int yLoc = e->pos().y();
  int width = viewport()->width();
  int height = viewport()->height();

  toolbar->updateVisibility(xLoc, yLoc, width, height);
  listWidget->updateVisibility(xLoc, yLoc, width, height);

  QWidget::mouseMoveEvent(e);
}
