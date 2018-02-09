#ifndef GRAPHICSVIEWRENDERER_H
#define GRAPHICSVIEWRENDERER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QResizeEvent>
#include <QStringList>

#include "renderer.h"

class GraphicsViewRenderer : public Renderer
{
    Q_OBJECT

public:
    explicit GraphicsViewRenderer(QWidget *parent = 0);
    ~GraphicsViewRenderer();

    QWidget* getEventReceiver() { return this; }
    void setDeck(Deck* deck);

    void resizeEvent(QResizeEvent* e);

private:
    QGraphicsView* view;
    QGraphicsScene* scene;
    QGraphicsTextItem* text;
    QGraphicsPixmapItem* graphicsPixmap;
    QPixmap pixmap;
    QFont font;
    int basicFontSize;
    float fontRatio;
    int shadowSize;
    float shadowRatio;
    int shadowOffset;
    float shadowOffsetRatio;
    QStringList sections;
    int currentSlide;
};

#endif // GRAPHICSVIEWRENDERER_H
