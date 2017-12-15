#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QDropEvent>
#include <QListView>
#include <QMimeData>
#include <QStringList>
#include <QStringListModel>

class PlaylistView : public QListView
{
    Q_OBJECT

  public:
    explicit PlaylistView(QWidget *parent = 0);
    ~PlaylistView();

    void dropEvent(QDropEvent* e);

  private:
    QStringListModel* model;
    QStringList strings;
};

#endif // PLAYLISTVIEW_H
