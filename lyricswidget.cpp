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
  lyricsList << "We wish you\na Merry Christmas\nWe wish you\na Merry Christmas"
             << "We wish you\na Merry Christmas\nAnd a happy new year!";
  orderList << "C1" << "C1";
  lyricsModel = new QStandardItemModel(2, 1, this);
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

}

LyricsWidget::~LyricsWidget()
{
}
