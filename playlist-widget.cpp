#include "playlist-widget.h"

#include <QSizePolicy>

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

  toolbar = new QWidget(this);
  toolbarLayout = new QHBoxLayout(toolbar);
  add = new QAction(QIcon("../add.png"), "&Add", toolbar);
  addButton = new QToolButton(toolbar);
  addButton->setDefaultAction(add);
  addButton->setAutoRaise(true);
  remove = new QAction(QIcon("../remove.png"), "&Remove", toolbar);
  removeButton = new QToolButton(toolbar);
  removeButton->setDefaultAction(remove);
  removeButton->setAutoRaise(true);
  save = new QAction(QIcon("../tango-icons/document-save.png"),
    "&Save", toolbar);
  saveButton = new QToolButton(toolbar);
  saveButton->setDefaultAction(save);
  saveButton->setAutoRaise(true);
  open = new QAction(QIcon("../tango-icons/document-open.png"),
    "&Open", toolbar);
  openButton = new QToolButton(toolbar);
  openButton->setDefaultAction(open);
  openButton->setAutoRaise(true);
  newPlaylist = new QAction(QIcon("../tango-icons/document-new.png"),
    "&New", toolbar);
  newPlaylistButton = new QToolButton(toolbar);
  newPlaylistButton->setDefaultAction(newPlaylist);
  newPlaylistButton->setAutoRaise(true);
  spacer = new QWidget(toolbar);
  spacer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);

  toolbarLayout->addWidget(openButton);
  toolbarLayout->addWidget(saveButton);
  toolbarLayout->addWidget(newPlaylistButton);
  toolbarLayout->addWidget(spacer);
  toolbarLayout->addWidget(addButton);
  toolbarLayout->addWidget(removeButton);

  layout->addWidget(toolbar);

  connect(removeButton, &QToolButton::clicked,
          view, &PlaylistView::removeSong);
  connect(addButton, &QToolButton::clicked,
          this, &PlaylistWidget::requestSong);
}

PlaylistWidget::~PlaylistWidget()
{
}

void
PlaylistWidget::addSong(const QString& str)
{
  view->addSong(str);
}
