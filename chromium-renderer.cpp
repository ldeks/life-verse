#include "chromium-renderer.h"
#include <QDir>

#include "deck.h"

ChromiumRenderer::ChromiumRenderer(QWidget *parent) :
    Renderer(parent)
{
  view = new QWebEngineView(this);
  layout->addWidget(view);

  // TODO: Test Default deck
  Deck defaultDeck;
  // The QUrl tells it where to go and find Reveal.js.
  view->setHtml(defaultDeck.genHtml(),
        QUrl::fromLocalFile(QDir::currentPath() + "/../"));

  /*
   * Locate the event receiver.
   * From stackoverflow.com/questions/43067680/ \
   * qt-webengine-simulate-mouse-event
   */
  foreach(QObject* obj, view->children())
  {
     QWidget* wgt = qobject_cast<QWidget*>(obj);
     if (wgt) {
       eventReceiver = wgt;
       break;
     }
  }
}

ChromiumRenderer::~ChromiumRenderer()
{
}

void
ChromiumRenderer::setDeck(Deck* deck)
{
  view->setHtml(deck->genHtml(),
        QUrl::fromLocalFile(QDir::currentPath() + "/../"));
}
