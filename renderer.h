#ifndef RENDERER_H
#define RENDERER_H

#include <QCloseEvent>
#include <QString>
#include <QWebEngineView>
#include <QWidget>

class Renderer : public QWebEngineView
{
    Q_OBJECT

public:
    explicit Renderer(QWidget *parent = 0);
    ~Renderer();

    void closeEvent(QCloseEvent* e);

    QWidget* getEventReceiver() { return eventReceiver; }

private:
    QString html;
    QWidget* eventReceiver;
};

#endif // RENDERER_H
