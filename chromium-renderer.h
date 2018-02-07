#ifndef CHROMIUMRENDERER_H
#define CHROMIUMRENDERER_H

#include <QWebEngineView>

#include "renderer.h"

class ChromiumRenderer : public Renderer
{
    Q_OBJECT

public:
    explicit ChromiumRenderer(QWidget *parent = 0);
    ~ChromiumRenderer();

    QWidget* getEventReceiver() { return eventReceiver; }
    void setDeck(Deck* deck);

private:
    QWebEngineView* view;
    QWidget* eventReceiver;
};

#endif // CHROMIUMRENDERER_H
