#include "songslist.h"

SongsList::SongsList(QWidget *parent) :
    QListView(parent)
{
  model = new QFileSystemModel(this);
  model->setRootPath("../content/songs/");
  setModel(model);
  setRootIndex(model->index("../content/songs/"));
  setMovement(QListView::Free);
  setDragEnabled(true);
}

SongsList::~SongsList()
{
}
