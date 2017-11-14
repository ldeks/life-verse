#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QCloseEvent>
#include <QFontComboBox>
#include <QHBoxLayout>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QListView>
#include <QResizeEvent>
#include <QStringListModel>
#include <QToolButton>
#include <QVBoxLayout>
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
    // The renderer
    QWebEngineView* view;
    QGraphicsProxyWidget* viewProxy;
    QGraphicsScene* scene;
    QString html;

    // The button bar.
    DarkPopupWidget* toolbar;
    QHBoxLayout* toolbarLayout;
    QAction* bold;
    QToolButton* boldButton;
    QAction* italic;
    QToolButton* italicButton;
    QFontComboBox* fontCombo;

    // Service item list.
    DarkPopupWidget* listWidget;
    QVBoxLayout* listLayout;
    QListView* listView;
    QStringListModel* listModel;
};

#endif // MAINWINDOW_H
