#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#include "playlist-view.h"
#include "song.h"

class PlaylistWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit PlaylistWidget(QWidget *parent = 0);
    ~PlaylistWidget();

  signals:
    void songSelected(Song* song);

  private:
    QVBoxLayout* layout;
    QLabel* label;
    PlaylistView* view;
};

#endif // PLAYLISTWIDGET_H
