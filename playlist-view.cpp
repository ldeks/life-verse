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

  connect(this, &PlaylistView::clicked, this, &PlaylistView::serveSong);
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
  QString str = e->mimeData()->text().mid(7);
  if (!song->loadFromFile(str)) {
    delete song;
    return;
  }

  songs.append(song);
  strings << song->getTitle();
  model->setStringList(strings);
  setCurrentIndex(model->index(strings.size() - 1));
  emit songSelected(song);
  e->acceptProposedAction();
}

void
PlaylistView::serveSong(const QModelIndex &index)
{
  emit songSelected(songs.at(index.row()));
}
