#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QDropEvent>
#include <QList>
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

  public slots:
    void addSong(const QString& filename);
    void removeSong();

  protected slots:
    void serveSong(const QModelIndex &index);

  signals:
    void songSelected(Song* song);

  private:
    QStringListModel* model;
    QStringList strings;
    QList<Song*> songs;
};

#endif // PLAYLISTVIEW_H
