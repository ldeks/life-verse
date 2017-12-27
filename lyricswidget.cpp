#include "lyricswidget.h"

#include <QKeyEvent>
#include <QHeaderView>
#include <QStandardItem>
#include <QApplication>

LyricsWidget::LyricsWidget(QWidget *parent) :
    QWidget(parent)
{
  // Lyrics.
  lyricsLayout = new QVBoxLayout(this);
  setLayout(lyricsLayout);
  lyricsLabel = new QLabel("Lyrics", this);
  lyricsView = new QTableView(this);
  lyricsView->installEventFilter(this);

  lyricsModel = NULL;
  lyricsView->horizontalHeader()->hide();
  lyricsView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  lyricsLayout->addWidget(lyricsLabel);
  lyricsLayout->addWidget(lyricsView);

}

LyricsWidget::~LyricsWidget()
{
}

void
LyricsWidget::setLyrics(QStringList lyrics, QStringList order)
{
  lyricsList = lyrics;
  orderList = order;
  bool firstTime = false;
  if (lyricsModel) {
    delete lyricsModel;
  }
  else {
    firstTime = true;
  }

  lyricsModel = new QStandardItemModel(lyricsList.size(), 1, this);
  for (int i = 0; i < lyricsList.size(); i++) {
    lyricsModel->setItem(i, 0, new QStandardItem(lyricsList.at(i)));
  }

  lyricsModel->setVerticalHeaderLabels(orderList);
  lyricsView->setModel(lyricsModel);

  // Have to set model first.
  if (firstTime) {
    baseRowHeight = lyricsView->rowHeight(0);
  }
  for (int i = 0; i < lyricsList.size(); i++) {
    int nrows = lyricsList.at(i).count("\n") + 1;
    lyricsView->setRowHeight(i, baseRowHeight*nrows*0.75);
  }

  lyricsView->selectRow(0);
}

bool
LyricsWidget::eventFilter(QObject* watched, QEvent* event)
{
  if ((watched == lyricsView) && (event->type() == QEvent::KeyPress)) {
     QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
     int key = keyEvent->key();
     switch (key) {
       case Qt::Key_Down:
         emit simpleKeyPress(key);
         break;
       case Qt::Key_Up:
         emit simpleKeyPress(key);
         break;
     }

     return false;
  }
  else {
    return QWidget::eventFilter(watched, event);
  }
}
