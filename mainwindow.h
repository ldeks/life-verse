#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QToolButton>
#include <QWebEngineView>
#include <QWidget>

#include "darkpopupwidget.h"

class MainWindow : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void resizeEvent(QResizeEvent* e);
    void closeEvent(QCloseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);

private:
    QWebEngineView* view;
    QGraphicsProxyWidget* viewProxy;
    QGraphicsScene* scene;
    QString html;

    DarkPopupWidget* toolbar;
    QHBoxLayout* toolbarLayout;
    QAction* bold;
    QToolButton* boldButton;
    QAction* italic;
    QToolButton* italicButton;
};

#endif // MAINWINDOW_H
