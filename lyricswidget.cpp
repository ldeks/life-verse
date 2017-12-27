#include "lyricswidget.h"

#include <QHeaderView>
#include <QStandardItem>

LyricsWidget::LyricsWidget(QWidget *parent) :
    QWidget(parent)
{
  // Lyrics.
  lyricsLayout = new QVBoxLayout(this);
  setLayout(lyricsLayout);
  lyricsLabel = new QLabel("Lyrics", this);
  lyricsView = new QTableView(this);

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
}
