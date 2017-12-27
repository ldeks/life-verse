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
  // Fake in some lyrics to test setLyrics.
  QStringList demoLyrics;
  QStringList demoOrder;
  demoLyrics << "Greater is the one\nliving inside of me"
             << "Than he who is\nliving in the world";
  demoOrder << "C1" << "C1";
  lyricsWidget->setLyrics(demoLyrics, demoOrder);
  demoLyrics << "Bring your doubt\nbring your shame"
             << "Bring your hurt\nand all your pain"
             << "Don't you know\nthat's not your name"
             << "You will always be\nmuch more to me.";
  demoOrder << "V1" << "V1" << "V1" << "V1";
  lyricsWidget->setLyrics(demoLyrics, demoOrder);
  previewRenderer = new Renderer(rightSplitter);
  rightSplitter->addWidget(lyricsWidget);
  rightSplitter->addWidget(previewRenderer);

  connect(playlistView, &PlaylistView::songSelected,
          this, &MainWindow::previewRenderSong);
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
