#include "playlist-view.h"

PlaylistView::PlaylistView(QWidget *parent) :
    QListView(parent)
{
  setAcceptDrops(true);
  setMovement(QListView::Free);
  setResizeMode(QListView::Adjust);
  model = new QStringListModel(this);
  strings << "Greater" << "Hosanna" << "Wonderful";
  model->setStringList(strings);
  setModel(model);
}

PlaylistView::~PlaylistView()
{
}

void
PlaylistView::dropEvent(QDropEvent* e)
{
  model->setStringList(strings);
  e->acceptProposedAction();
}
