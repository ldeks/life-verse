#ifndef DARKPOPUPWIDGET_H
#define DARKPOPUPWIDGET_H

#include <QFrame>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QString>

class DarkPopupWidget : public QFrame
{
    Q_OBJECT

public:
    explicit DarkPopupWidget(QWidget *parent = 0);
    ~DarkPopupWidget();

    void addCSS(QString text) { css += text; setStyleSheet(css); }
    void addToScene(QGraphicsScene* scene);
    void setPositionWeights(float horizontalWeight, float verticalWeight);
    void updatePosition(int width, int height);
    void updateVisibility(int xLoc, int yLoc, int width, int height);
    void setXPadding(int xpad) { xPadding = xpad ; }
    void setYPadding(int ypad) { yPadding = ypad ; }

private:
    QString css;
    QGraphicsProxyWidget* proxyWidget;
    float hWeight;
    float vWeight;
    int xPadding;
    int yPadding;
};

#endif // DARKPOPUPWIDGET_H
