#include "playlist-view.h"

PlaylistView::PlaylistView(QWidget *parent) :
    QListView(parent)
{
  setMovement(QListView::Free);
  setResizeMode(QListView::Adjust);
  model = new QStringListModel(this);
  model->setStringList(strings);
  setModel(model);
  setAcceptDrops(true);
}

PlaylistView::~PlaylistView()
{
}

void
PlaylistView::dragEnterEvent(QDragEnterEvent* e)
{
  e->acceptProposedAction();
}

void
PlaylistView::dragMoveEvent(QDragMoveEvent* e)
{
  e->acceptProposedAction();
}

void
PlaylistView::dropEvent(QDropEvent* e)
{
  Song* song = new Song();
  //QUrl url = e->mimeData()->text();
  //QString str = url.toLocalFile();
  QString str = e->mimeData()->text().mid(7);
  if (!song->loadFromFile(str)) {
    delete song;
    return;
  }

  strings << song->getTitle();
  model->setStringList(strings);
  e->acceptProposedAction();
  emit haveSong(song);
}
