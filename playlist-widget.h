#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QAction>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
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

    bool savePlaylistAs(QString fname);

  signals:
    void songSelected(Song* song);
    void requestSong();

  public slots:
    void addSong(const QString& str);
    void createNewPlaylist();
    void openPlaylist();
    void savePlaylist();
    void setModifiedLabel();

  private:
    QVBoxLayout* layout;
    QLabel* label;
    PlaylistView* view;
    QWidget* toolbar;
    QHBoxLayout* toolbarLayout;
    QAction* newPlaylist;
    QToolButton* newPlaylistButton;
    QAction* save;
    QToolButton* saveButton;
    QAction* open;
    QToolButton* openButton;
    QWidget* spacer;
    QAction* add;
    QToolButton* addButton;
    QAction* remove;
    QToolButton* removeButton;
    bool saved;
    QString saveName;
};

#endif // PLAYLISTWIDGET_H
