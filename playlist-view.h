#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QDropEvent>
#include <QListView>
#include <QMimeData>
#include <QStringList>
#include <QStringListModel>

#include "song.h"

class PlaylistView : public QListView
{
    Q_OBJECT

  public:
    explicit PlaylistView(QWidget *parent = 0);
    ~PlaylistView();

    void dragEnterEvent(QDragEnterEvent* e);
    void dragMoveEvent(QDragMoveEvent* e);
    void dropEvent(QDropEvent* e);

  signals:
    void haveSong(Song* song);

  private:
    QStringListModel* model;
    QStringList strings;
};

#endif // PLAYLISTVIEW_H
