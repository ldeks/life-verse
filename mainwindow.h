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

class MainWindow : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void resizeEvent(QResizeEvent* e);
    void closeEvent(QCloseEvent* e);

private:
    void positionToolbar();

    QWebEngineView* view;
    QGraphicsProxyWidget* viewProxy;
    QGraphicsScene* scene;
    QString html;

    QFrame* toolbar;
    QHBoxLayout* toolbarLayout;
    QAction* bold;
    QToolButton* boldButton;
    QAction* italic;
    QToolButton* italicButton;
    QGraphicsProxyWidget* toolbarProxy;
};

#endif // MAINWINDOW_H
