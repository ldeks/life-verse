#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileSystemModel>
#include <QLabel>
#include <QMainWindow>
#include <QSplitter>
#include <QTableView>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "renderer.h"
#include "playlist-view.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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
    //TODO: FilterBar songsFilter;
    QListView* songsList;
    QFileSystemModel* songsModel;
    QWidget* bibles;

    //Right side
    QSplitter* rightSplitter;
    QWidget* lyricsWidget;
    QVBoxLayout* lyricsLayout;
    QLabel* lyricsLabel;
    QTableView* lyricsView;
    //TODO: Various toolbars here.
    Renderer* previewRenderer;
};

#endif // MAINWINDOW_H
