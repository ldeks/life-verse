#include "mainwindow.h"

#include <QApplication>
#include <QKeyEvent>
#include <QTimer>
#include <QVector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), mainRenderer(NULL)
{
  songDeck = new Deck(this);

  // Central Widget
  mainSplitter = new QSplitter(this);
  leftSplitter = new QSplitter(Qt::Vertical, mainSplitter);
  rightSplitter = new QSplitter(Qt::Vertical, mainSplitter);
  mainSplitter->addWidget(leftSplitter);
  mainSplitter->addWidget(rightSplitter);
  setCentralWidget(mainSplitter);

  // Left side.
  playlistWidget = new PlaylistWidget(leftSplitter);
  mediaTabs = new QTabWidget(leftSplitter);
  leftSplitter->addWidget(playlistWidget);
  leftSplitter->addWidget(mediaTabs);

  // Media tabs.
  songsList = new SongsList(mediaTabs);
  bibles = new QWidget(mediaTabs);
  mediaTabs->addTab(songsList, "Songs");
  // mediaTabs->addTab(bibles, "Bibles");

  // Right side.
  lyricsWidget = new LyricsWidget(rightSplitter);
  previewRenderer = new Renderer(rightSplitter);
  filmstrip = new Filmstrip(rightSplitter);
  rightSplitter->addWidget(lyricsWidget);
  rightSplitter->addWidget(previewRenderer);
  rightSplitter->addWidget(filmstrip);

  connect(playlistWidget, &PlaylistWidget::songSelected,
          this, &MainWindow::renderSong);
  connect(playlistWidget, &PlaylistWidget::songSelected,
          this, &MainWindow::setLyrics);
  connect(lyricsWidget, &LyricsWidget::simpleKeyPress,
          this, &MainWindow::transferSimpleKeyPress);
  connect(lyricsWidget, &LyricsWidget::slideSelected,
          this, &MainWindow::transferMouseClick);
  connect(filmstrip, &Filmstrip::imageSelected,
          this, &MainWindow::renderImage);
  connect(playlistWidget, &PlaylistWidget::requestSong,
          songsList, &SongsList::getSong);
  connect(songsList, &SongsList::sendSongPath,
          playlistWidget, &PlaylistWidget::addSong);
}

MainWindow::~MainWindow()
{
}

void
MainWindow::render()
{
  QString html = songDeck->genHtml();
  QUrl url = QUrl::fromLocalFile("/home/laura/programming/life-verse/");
  previewRenderer->setHtml(html, url);
  mainRenderer->setHtml(html, url);
}

void
MainWindow::renderSong(Song* song)
{
  songDeck->setSections(song->toDeckSections());
  render();
}

void
MainWindow::renderImage(const QString &name)
{
  int idx = lyricsWidget->currentIndex();
  songDeck->setStillLink(name);
  render();
  // We need to give the web engine some time to reload the page.
  QTimer::singleShot(100, [=] { transferMouseClick(idx); });
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
