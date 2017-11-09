#include "darkpopupwidget.h"

DarkPopupWidget::DarkPopupWidget(QWidget *parent) :
    QFrame(parent), hWeight(0), vWeight(0), xPadding(25), yPadding(25)
{
  setWindowOpacity(0.7);
  css += "QFrame { background: dark-gray }";
  setStyleSheet(css);
  setVisible(false);
}

DarkPopupWidget::~DarkPopupWidget()
{
}

void
DarkPopupWidget::addToScene(QGraphicsScene* scene) {
  proxyWidget = scene->addWidget(this);
}

void
DarkPopupWidget::setPositionWeights(float horizontalWeight,
                                    float verticalWeight) {
  hWeight = horizontalWeight;
  vWeight = verticalWeight;
}

void
DarkPopupWidget::updatePosition(int width, int height) {
  proxyWidget->setPos(hWeight*width, vWeight*height);
}

void
DarkPopupWidget::updateVisibility(int xLoc, int yLoc, int width, int height) {
  int xTopPos = hWeight*width;
  int yTopPos = vWeight*height;
  if (((xLoc >= xTopPos - xPadding) &&
       (xLoc < xTopPos + this->width() + xPadding)) &&
      ((yLoc >= yTopPos - yPadding) &&
       (yLoc < yTopPos + this->height() + yPadding))) {
    proxyWidget->setVisible(true);
  } else {
    proxyWidget->setVisible(false);
  }
}
