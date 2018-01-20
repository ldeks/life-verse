#include "playlist-widget.h"

#include <QSizePolicy>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

PlaylistWidget::PlaylistWidget(QWidget *parent) :
    QWidget(parent), saved(false)
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
  connect(saveButton, &QToolButton::clicked,
          this, &PlaylistWidget::savePlaylist);
  connect(newPlaylistButton, &QToolButton::clicked,
          this, &PlaylistWidget::createNewPlaylist);
  connect(view, &PlaylistView::hasBeenModified,
          this, &PlaylistWidget::setModifiedLabel);
  connect(openButton, &QToolButton::clicked,
          this, &PlaylistWidget::openPlaylist);
}

PlaylistWidget::~PlaylistWidget()
{
}

void
PlaylistWidget::addSong(const QString& str)
{
  view->addSong(str);
}

void
PlaylistWidget::setModifiedLabel()
{
  QString fileLabel = label->text();
  if (fileLabel.at(fileLabel.size() - 1) != "*")
    label->setText(label->text() + "*");
  saved = false;
}

void
PlaylistWidget::savePlaylist()
{
  if (saved && !view->isModified())
    return;

  if (saveName.isEmpty())
  {
    saveName = QFileDialog::getSaveFileName(this, "Save File",
      "../content/playlists/unnamed-playlist");

    if (saveName.isEmpty())
      return;
  }

  if (!savePlaylistAs(saveName))
    return;

  int pos = saveName.indexOf("content/playlists/")
    + QString("content/playlists/").size();

  label->setText("Playlist - " + saveName.mid(pos));
  saved = true;
}

bool
PlaylistWidget::savePlaylistAs(QString fname)
{
  QFile file (fname);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return false;

  QTextStream out(&file);
  out << "<!DOCTYPE life-verse-playlist-0.1/>" << "\n";
  out << view->getFilenames().join("\n");
  file.close();

  return true;
}

void
PlaylistWidget::createNewPlaylist()
{
  if (view->isEmpty())
    return;

  if (!saved && view->isModified())
  {
    QMessageBox::StandardButton ret;
    ret = QMessageBox::question(this, "Playlist not saved.",
      "Would you like to save the current playlist?",
      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
      QMessageBox::Save);
    if (ret == QMessageBox::Cancel) {
      return;
    }
    else if (ret == QMessageBox::Save) {
      savePlaylist();
      if (!saved)
        return;
    }
  }

  label->setText("Playlist");
  view->clear();
  saveName = QString();
  saved = true;
}

void
PlaylistWidget::openPlaylist()
{
  createNewPlaylist();
  if (!view->isEmpty())
    return;

  QString fname = QFileDialog::getOpenFileName(this, "Open File",
    "../content/playlists/");

  if (fname.isEmpty())
    return;

  QFile file (fname);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  QTextStream in(&file);
  QString magicString = in.readLine();
  QStringList songNames;
  if (magicString == "<!DOCTYPE life-verse-playlist-0.1/>")
  {
    while (!in.atEnd()) {
      songNames << in.readLine();
    }
  }
  file.close();

  view->addSongs(songNames);
  int pos = fname.indexOf("content/playlists/")
    + QString("content/playlists/").size();

  label->setText("Playlist - " + fname.mid(pos));
  view->setModified(false);
  saved = true;
  saveName = fname;
}
