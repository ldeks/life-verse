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
  QString str = e->mimeData()->text();
  addSong(str);
  e->acceptProposedAction();
}

void
PlaylistView::addSong(const QString& filename)
{
  Song* song = new Song();
  if (!song->loadFromFile(filename)) {
    delete song;
    return;
  }

  songs.append(song);
  strings << song->getTitle();
  model->setStringList(strings);
  setCurrentIndex(model->index(strings.size() - 1));
  emit songSelected(song);
}

void
PlaylistView::serveSong(const QModelIndex &index)
{
  emit songSelected(songs.at(index.row()));
}

void
PlaylistView::removeSong()
{
  if (strings.size() < 1)
    return;

  int row = currentIndex().row();
  strings.removeAt(row);
  model->setStringList(strings);
  delete songs.at(row);
  songs.removeAt(row);

  int lastIdx = songs.size() - 1;
  if (lastIdx >= 0)
  {
    setCurrentIndex(model->index(lastIdx));
    emit songSelected(songs.at(lastIdx));
  }
}
