#include "renderer.h"
#include <QCoreApplication>
#include <QFile>
#include <QIcon>
#include <QTextStream>
#include <QRectF>
#include <QString>
#include <QStringList>
#include <QUrl>

#include "deck.h"
#include "song.h"

Renderer::Renderer(QWidget *parent) :
    QGraphicsView(parent)
{
  // Renderer setup.
  view = new QWebEngineView();
  scene = new QGraphicsScene(this);
  viewProxy = scene->addWidget(view);
  setScene(scene);
  setMouseTracking(true);

  // TODO: Test from hand-edited file.
  //QFile file("../helloworld.html");
  //if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  //  return;

  //QTextStream in (&file);
  //html = in.readAll();
  //view->setHtml(html, QUrl::fromLocalFile("/home/laura/programming/life-verse/"));
  // view->load(QUrl("http://localhost:3000/helloworld.html"));

  // TODO: Test Default deck
  Deck defaultDeck;
  // The QUrl tells it where to go and find Reveal.js.
  view->setHtml(defaultDeck.genHtml(),
        QUrl::fromLocalFile("/home/laura/programming/life-verse/"));
  // TODO: Remove. For debugging right now.
  defaultDeck.writeFile();

  // TODO: Test song reading.
  // QFile file("../foo.bar");
  // if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
  //   return;
  // QTextStream out (&file);
  // Song fishbowl;
  // fishbowl.loadFromFile("../content/songs/10000-reasons");
  // out << "Title: " << fishbowl.getTitle() << endl;
  // out << "Author: " << fishbowl.getAuthor() << endl;
  // out << "Order: " << fishbowl.getOrder().join(' ') << endl;
  // out << "V1: " << fishbowl.getStanzas("verse 1").join("\n!!!!!\n") << endl;
  // out << endl;
  // out << "V2: " << fishbowl.getStanzas("verse 2").join("\n!!!!!\n") << endl;
  // out << endl;
  // out << "V3: " << fishbowl.getStanzas("verse 3").join("\n!!!!!\n") << endl;
  // out << endl;
  // out << "C1: " << fishbowl.getStanzas("chorus 1").join("\n!!!!!\n") << endl;
  // file.close();

  // TODO: Test song and deck and view integration. :)
  // Deck greaterDeck;
  // Song greater;
  // greater.loadFromFile("../content/songs/greater");
  // greaterDeck.setSections(greater.toDeckSections());
  // greaterDeck.setStillLink("");
  // greaterDeck.setVideoLink("https://player.vimeo.com/external/188557098.hd.mp4?s=911c1c900d991c43cec89ed87bd2578ca7060d4c&profile_id=174&oauth2_token_id=57447761");
  // view->setHtml(greaterDeck.genHtml(),
  //   QUrl::fromLocalFile("/home/laura/programming/life-verse/"));
  // greaterDeck.writeFile();

  // TODO: Test Google Slides integration. Maybe needs embed? something about
  // unsecure script.  The controls failed to load.
  //view->load(QUrl("https://docs.google.com/presentation/d/e/2PACX-1vR98KVEcwhhDH7xVSfkCEQKm3ujGp-S4i-8659EFKb_r59kgoiDxkQoBmdm0J20iGzo-Za8NX1q1fo4/pub?start=true&loop=true&delayms=10000"));

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
  addButton = new QPushButton("+", listWidget);
  listLayout->addWidget(addButton);
  listWidget->setLayout(listLayout);

  listWidget->addToScene(scene);
  listWidget->setMinimumSize(200, 400);
  listWidget->setPositionWeights(0.02, 0.3);
  listWidget->updatePosition(viewport()->width(), viewport()->height());
}

Renderer::~Renderer()
{
  delete view;
  delete toolbar;
  delete listWidget;
  QCoreApplication::quit();
}

void
Renderer::resizeEvent(QResizeEvent* e) {
  viewProxy->setGeometry(QRectF(viewport()->rect()));
  toolbar->updatePosition(viewport()->width(), viewport()->height());
  listWidget->updatePosition(viewport()->width(), viewport()->height());
}

void
Renderer::closeEvent(QCloseEvent* e) {
  QCoreApplication::quit();
}

void
Renderer::mouseMoveEvent(QMouseEvent* e) {
  int xLoc = e->pos().x();
  int yLoc = e->pos().y();
  int width = viewport()->width();
  int height = viewport()->height();

  toolbar->updateVisibility(xLoc, yLoc, width, height);
  listWidget->updateVisibility(xLoc, yLoc, width, height);

  QWidget::mouseMoveEvent(e);
}
