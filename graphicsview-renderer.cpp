#include "graphicsview-renderer.h"
#include <QDir>
#include <QTextBlockFormat>
#include <QTextCursor>

GraphicsViewRenderer::GraphicsViewRenderer(QWidget *parent) :
    Renderer(parent)
{
  view = new QGraphicsView(this);
  layout->addWidget(view);
  scene = new QGraphicsScene(this);
  currentSlide = 0;

  Deck defaultDeck;
  pixmap = QPixmap(QDir::currentPath() + "/../" + defaultDeck.getStillLink());
  basicFontSize = defaultDeck.getFontSize() * 0.14; // before window scaling.
  font = QFont(defaultDeck.getFontFamily(), basicFontSize);
  fontRatio = 0.85/500.0; // The scaling ratio for the font.
  // This is a strange relationship.  Qt and CSS differ a lot.
  font.setWeight((defaultDeck.getFontWeight().toInt()-100) * (87.0/800) + 12);
  shadowSize = defaultDeck.getFontShadowSize();
  shadowRatio = 0.5 * shadowSize/float(16);
  shadowOffset = 2;
  shadowOffsetRatio = shadowOffset/float(16);
  sections = defaultDeck.getSections();
  sections.replaceInStrings("<br>", "\n");

  text = scene->addText(sections.at(currentSlide), font);
  text->setDefaultTextColor(defaultDeck.getFontColor());
  text->setFlags(QGraphicsItem::ItemIsSelectable |
                 QGraphicsItem::ItemIsMovable);
  text->setTextInteractionFlags(Qt::TextEditorInteraction);
  text->setZValue(1);
  graphicsPixmap = scene->addPixmap(pixmap);

  // From cesarbs.org - you have to literally go through Win95 Word gui
  // interaction steps to center the text :(
  text->setTextWidth(0.95 * pixmap.width());
  QTextBlockFormat format;
  format.setAlignment(Qt::AlignCenter);
  QTextCursor cursor = text->textCursor();
  cursor.select(QTextCursor::Document);
  cursor.mergeBlockFormat(format);
  cursor.clearSelection();
  text->setTextCursor(cursor);

  view->setScene(scene);
}

GraphicsViewRenderer::~GraphicsViewRenderer()
{
  delete text;
  delete graphicsPixmap;
}

void
GraphicsViewRenderer::setDeck(Deck* deck)
{
}

void
GraphicsViewRenderer::resizeEvent(QResizeEvent* e)
{
   // self.adjustText()
   int fontSize = basicFontSize * fontRatio * width();
   font.setPointSizeF(fontSize);
   shadowSize = int(fontSize * shadowRatio);
   shadowOffset = int(fontSize * shadowOffsetRatio);
   text->setFont(font);

   // self.scene.setSceneRect(QRectF(self.viewport().rect()))
   scene->setSceneRect(QRectF(rect()));

   // self.centerText()
   // The center of the window
   QPointF centerPos = QPointF(float(width())/2, float(height())/2);

   // The desired new location
   QRectF rect = text->boundingRect();
   QPointF topLeftPos = centerPos - QPointF(rect.width()/2, rect.height()/2);

   // Any position of the text relative to the scene
   QRectF rectS = text->mapRectToScene(rect);

   // Move the text to the center position
   text->moveBy(topLeftPos.x()-rectS.x(), topLeftPos.y()-rectS.y());
}
