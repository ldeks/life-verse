#include <QHeaderView>
#include <QStandardItem>

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
  lyricsWidget = new QWidget(rightSplitter);
  previewRenderer = new Renderer(rightSplitter);
  rightSplitter->addWidget(lyricsWidget);
  rightSplitter->addWidget(previewRenderer);

  // Lyrics.
  lyricsLayout = new QVBoxLayout(lyricsWidget);
  lyricsWidget->setLayout(lyricsLayout);
  lyricsLabel = new QLabel("Lyrics", lyricsWidget);
  lyricsView = new QTableView(lyricsWidget);
  lyricsList << "We wish you\na Merry Christmas\nWe wish you\na Merry Christmas"
             << "We wish you\na Merry Christmas\nAnd a happy new year!";
  orderList << "C1" << "C1";
  lyricsModel = new QStandardItemModel(2, 1, lyricsWidget);
  lyricsModel->setItem(0, 0, new QStandardItem(lyricsList.at(0)));
  lyricsModel->setItem(1, 0, new QStandardItem(lyricsList.at(1)));
  lyricsView->setModel(lyricsModel);
  lyricsView->horizontalHeader()->hide();
  lyricsView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  lyricsModel->setVerticalHeaderLabels(orderList);
  for (int i = 0; i < lyricsView->verticalHeader()->count(); i++) {
    int nrows = lyricsList.at(i).count("\n") + 1;
    lyricsView->setRowHeight(i, lyricsView->rowHeight(i)*nrows*0.75);
  }
  lyricsView->verticalHeader();
  lyricsLayout->addWidget(lyricsLabel);
  lyricsLayout->addWidget(lyricsView);

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
