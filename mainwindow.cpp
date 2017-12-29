#include "mainwindow.h"

#include <QApplication>
#include <QKeyEvent>
#include <QVector>

#include "deck.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), mainRenderer(NULL)
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
  filmstrip = new Filmstrip(rightSplitter);
  rightSplitter->addWidget(lyricsWidget);
  rightSplitter->addWidget(previewRenderer);
  rightSplitter->addWidget(filmstrip);

  connect(playlistView, &PlaylistView::songSelected,
          this, &MainWindow::renderSong);
  connect(playlistView, &PlaylistView::songSelected,
          this, &MainWindow::setLyrics);
  connect(lyricsWidget, &LyricsWidget::simpleKeyPress,
          this, &MainWindow::transferSimpleKeyPress);
  connect(lyricsWidget, &LyricsWidget::slideSelected,
          this, &MainWindow::transferMouseClick);
}

MainWindow::~MainWindow()
{
}

void
MainWindow::renderSong(Song* song)
{
  Deck songDeck;
  songDeck.setSections(song->toDeckSections());
  QString html = songDeck.genHtml();
  QUrl url = QUrl::fromLocalFile("/home/laura/programming/life-verse/");
  previewRenderer->setHtml(html, url);
  emit syncHtml(html, url);
}

void
MainWindow::setLyrics(Song* song)
{
  lyricsWidget->setLyrics(song->toLyricSections(), song->getLyricOrder());
}

void
MainWindow::transferSimpleKeyPress(int key)
{
   // Translate between lyrics menu and reveal.js.
   switch (key) {
     case (Qt::Key_Down):
       key = Qt::Key_Right;
       break;
     case (Qt::Key_Up):
       key = Qt::Key_Left;
       break;
   }
   // Must be separate because sendEvent takes ownership.
   QKeyEvent previewRendererKey (QEvent::KeyPress, key, Qt::NoModifier);
   QApplication::sendEvent(previewRenderer, &previewRendererKey);
   QKeyEvent rendererKey (QEvent::KeyPress, key, Qt::NoModifier);
   QApplication::sendEvent(mainRenderer, &rendererKey);
}

void
MainWindow::transferMouseClick(int idx)
{
   QVector<Renderer*> rvec;
   rvec.append(previewRenderer);
   rvec.append(mainRenderer);
   for (int i = 0; i < 2; i++) {
     QKeyEvent home (QEvent::KeyPress, Qt::Key_Home, Qt::NoModifier);
     QApplication::sendEvent(rvec.at(i), &home);
     for (int j = 0; j < idx; j++) {
       QKeyEvent right (QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
       QApplication::sendEvent(rvec.at(i), &right);
     }
   }
}
