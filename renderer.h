#ifndef RENDERER_H
#define RENDERER_H

#include <QAction>
#include <QCloseEvent>
#include <QFontComboBox>
#include <QHBoxLayout>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QListView>
#include <QPushButton>
#include <QResizeEvent>
#include <QString>
#include <QStringListModel>
#include <QToolButton>
#include <QUrl>
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QWidget>

#include "darkpopupwidget.h"

class Renderer : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Renderer(QWidget *parent = 0);
    ~Renderer();

    void resizeEvent(QResizeEvent* e);
    void closeEvent(QCloseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);

    void setHtml(const QString& html, const QUrl& url = QUrl());

private:
    // The renderer
    QWebEngineView* view;
    QGraphicsProxyWidget* viewProxy;
    QGraphicsScene* scene;
    QString html;

    //  // The button bar.
    //  DarkPopupWidget* toolbar;
    //  QHBoxLayout* toolbarLayout;
    //  QAction* bold;
    //  QToolButton* boldButton;
    //  QAction* italic;
    //  QToolButton* italicButton;
    //  QFontComboBox* fontCombo;

    //  // Service item list.
    //  DarkPopupWidget* listWidget;
    //  QVBoxLayout* listLayout;
    //  QListView* listView;
    //  QStringListModel* listModel;
    //  QPushButton* addButton;
};

#endif // RENDERER_H
