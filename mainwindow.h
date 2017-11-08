#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QWebEngineView>

class MainWindow : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void resizeEvent(QResizeEvent* e);
    void closeEvent(QCloseEvent* e);

private:
    QWebEngineView* view;
    QGraphicsProxyWidget* viewProxy;
    QGraphicsScene* scene;
    QString html;
};

#endif // MAINWINDOW_H
