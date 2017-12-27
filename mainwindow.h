#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QSplitter>
#include <QTabWidget>
#include <QUrl>
#include <QVBoxLayout>
#include <QWidget>

#include "renderer.h"
#include "lyricswidget.h"
#include "playlist-view.h"
#include "songslist.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  public slots:
    void renderSong(Song* song);
    void setLyrics(Song* song);

  signals:
    void syncHtml(QString html, QUrl url);

  private:
    //Central widget
    QSplitter* mainSplitter;

    //Left side
    QSplitter* leftSplitter;
    //Playlist
    QWidget* playlistWidget;
    QVBoxLayout* playlistLayout;
    QLabel* playlistLabel;
    PlaylistView* playlistView;
    //Media tabs.
    QTabWidget* mediaTabs;
    SongsList* songsList;
    QWidget* bibles;

    //Right side
    QSplitter* rightSplitter;
    LyricsWidget* lyricsWidget;
    //TODO: Various toolbars here.
    Renderer* previewRenderer;
};

#endif // MAINWINDOW_H
