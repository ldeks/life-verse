#include "mainwindow.h"
#include "deck.h"

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
  lyricsWidget = new LyricsWidget(rightSplitter);
  previewRenderer = new Renderer(rightSplitter);
  rightSplitter->addWidget(lyricsWidget);
  rightSplitter->addWidget(previewRenderer);

  connect(playlistView, &PlaylistView::songSelected,
          this, &MainWindow::previewRenderSong);
  connect(playlistView, &PlaylistView::songSelected,
          this, &MainWindow::setLyrics);
}

MainWindow::~MainWindow()
{
}

void
MainWindow::previewRenderSong(Song* song)
{
  Deck songDeck;
  songDeck.setSections(song->toDeckSections());
  previewRenderer->setHtml(songDeck.genHtml(),
    QUrl::fromLocalFile("/home/laura/programming/life-verse/"));
}

void
MainWindow::setLyrics(Song* song)
{
  lyricsWidget->setLyrics(song->toLyricSections(), song->getLyricOrder());
}
