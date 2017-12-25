#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QSplitter>
#include <QStandardItemModel>
#include <QTableView>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "renderer.h"
#include "playlist-view.h"
#include "songslist.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  public slots:
    void previewRenderSong(Song* song);

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
    QWidget* lyricsWidget;
    QVBoxLayout* lyricsLayout;
    QLabel* lyricsLabel;
    QTableView* lyricsView;
    QStandardItemModel* lyricsModel;
    QStringList lyricsList;
    QStringList orderList;
    //TODO: Various toolbars here.
    Renderer* previewRenderer;
};

#endif // MAINWINDOW_H
