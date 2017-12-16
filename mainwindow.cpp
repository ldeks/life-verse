#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
  // Central Widget
  mainSplitter = new QSplitter(this);
  leftSplitter = new QSplitter(Qt::Vertical, mainSplitter);
  rightSplitter = new QSplitter(Qt::Vertical, mainSplitter);
  mainSplitter->addWidget(leftSplitter);
  mainSplitter->addWidget(rightSplitter);
  setCentralWidget(mainSplitter);

  // Left side.
  playlistWidget = new QWidget(leftSplitter);
  mediaTabs = new QTabWidget(leftSplitter);
  leftSplitter->addWidget(playlistWidget);
  leftSplitter->addWidget(mediaTabs);

  // Playlist
  playlistLayout = new QVBoxLayout(playlistWidget);
  playlistLabel = new QLabel("Playlist", playlistWidget);
  playlistView = new PlaylistView(playlistWidget);
  playlistLayout->addWidget(playlistLabel);
  playlistLayout->addWidget(playlistView);
  playlistWidget->setLayout(playlistLayout);

  // Media tabs.
  songsList = new SongsList(mediaTabs);
  bibles = new QWidget(mediaTabs);
  mediaTabs->addTab(songsList, "Songs");
  mediaTabs->addTab(bibles, "Bibles");

  // Right side.
  lyricsWidget = new QWidget(rightSplitter);
  previewRenderer = new Renderer(rightSplitter);
  rightSplitter->addWidget(lyricsWidget);
  rightSplitter->addWidget(previewRenderer);

  // Lyrics.
  lyricsLayout = new QVBoxLayout(lyricsWidget);
  lyricsWidget->setLayout(lyricsLayout);
  lyricsLabel = new QLabel("Lyrics", lyricsWidget);
  lyricsView = new QTableView(lyricsWidget);
  lyricsLayout->addWidget(lyricsLabel);
  lyricsLayout->addWidget(lyricsView);
}

MainWindow::~MainWindow()
{
}
