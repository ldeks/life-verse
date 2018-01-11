#include "playlist-widget.h"

PlaylistWidget::PlaylistWidget(QWidget *parent) :
    QWidget(parent)
{
  layout = new QVBoxLayout(this);
  label = new QLabel("Playlist", this);
  view = new PlaylistView(this);
  layout->addWidget(label);
  layout->addWidget(view);
  setLayout(layout);

  connect(view, &PlaylistView::songSelected,
          this, &PlaylistWidget::songSelected);
}

PlaylistWidget::~PlaylistWidget()
{
}
