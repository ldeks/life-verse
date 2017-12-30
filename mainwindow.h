#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QSplitter>
#include <QTabWidget>
#include <QUrl>
#include <QVBoxLayout>
#include <QWidget>

#include "deck.h"
#include "filmstrip.h"
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

    void setMainRenderer(Renderer* r) { mainRenderer = r; }

  public slots:
    void renderSong(Song* song);
    void renderImage(const QString &name);
    void setLyrics(Song* song);
    void transferSimpleKeyPress(int key);
    void transferMouseClick(int idx);

  private:
    void render();

    //External
    Renderer* mainRenderer; // Does NOT own!
    Deck* songDeck;

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
    Filmstrip* filmstrip;
};

#endif // MAINWINDOW_H
