#include "renderer.h"
#include <QCoreApplication>
#include <QDir>

#include "deck.h"

Renderer::Renderer(QWidget *parent) :
    QWebEngineView(parent)
{
  // TODO: Test Default deck
  Deck defaultDeck;
  // The QUrl tells it where to go and find Reveal.js.
  setHtml(defaultDeck.genHtml(),
        QUrl::fromLocalFile(QDir::currentPath() + "/../"));

  /*
   * Locate the event receiver.
   * From stackoverflow.com/questions/43067680/ \
   * qt-webengine-simulate-mouse-event
   */
  foreach(QObject* obj, children())
  {
     QWidget* wgt = qobject_cast<QWidget*>(obj);
     if (wgt) {
       eventReceiver = wgt;
       break;
     }
  }
}

Renderer::~Renderer()
{
  QCoreApplication::quit();
}

void
Renderer::closeEvent(QCloseEvent* e) {
  QCoreApplication::quit();
}
