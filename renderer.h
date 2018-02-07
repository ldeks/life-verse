#ifndef RENDERER_H
#define RENDERER_H

#include <QCloseEvent>
#include <QString>
#include <QUrl>
#include <QVBoxLayout>
#include <QWidget>

#include "deck.h"

class Renderer : public QWidget
{
    Q_OBJECT

public:
    explicit Renderer(QWidget *parent = 0);
    ~Renderer();

    void closeEvent(QCloseEvent* e);

    virtual QWidget* getEventReceiver() = 0;

    virtual void setDeck(Deck* deck) = 0;

protected:
    QVBoxLayout* layout;
};

#endif // RENDERER_H
