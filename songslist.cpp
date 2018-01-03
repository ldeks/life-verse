#include "songslist.h"

SongsList::SongsList(QWidget *parent) :
    QWidget(parent)
{
  vLayout = new QVBoxLayout(this);
  setLayout(vLayout);
  list = new QListView(this);

  model = new QFileSystemModel(this);
  model->setRootPath("../content/songs/");

  list->setModel(model);
  list->setRootIndex(model->index("../content/songs/"));
  list->setMovement(QListView::Free);
  list->setDragEnabled(true);

  vLayout->addWidget(list);
}

SongsList::~SongsList()
{
}
