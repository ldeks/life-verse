#include "songslist.h"

SongsList::SongsList(QWidget *parent) :
    QWidget(parent)
{
  vLayout = new QVBoxLayout(this);
  setLayout(vLayout);
  list = new QListView(this);

  dir = QDir("../content/songs/");
  filenames = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
  model = new SongsListModel(this);
  model->setFilePath(dir.absolutePath() + "/");
  model->setFileNames(filenames);
  QStringList prettyNames = filenames; // ReplaceInStrings works in place.
  model->setStringList(prettyNames.replaceInStrings("-", " "));

  proxyModel = new QSortFilterProxyModel(this);
  proxyModel->setSourceModel(model);
  proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

  list->setModel(proxyModel);
  list->setMovement(QListView::Free);
  list->setDragEnabled(true);

  filter = new QLineEdit(this);
  filter->setClearButtonEnabled(true);
  filter->setPlaceholderText("Search songs");

  vLayout->addWidget(filter);
  vLayout->addWidget(list);

  connect(filter, &QLineEdit::textChanged,
          proxyModel, &QSortFilterProxyModel::setFilterFixedString);
}

SongsList::~SongsList()
{
}

SongsListModel::SongsListModel(QWidget *parent) :
    QStringListModel(parent)
{
}

SongsListModel::~SongsListModel()
{
}

QMimeData*
SongsListModel::mimeData(const QModelIndexList &indexes) const
{
  if (indexes.size() != 1) // Two or more doesn't make sense here.
    return 0;

  QMimeData* data = new QMimeData();
  data->setText(path + fileNames.at(indexes.at(0).row()));

  return data;
}

void
SongsList::getSong()
{
  if (!list->currentIndex().isValid())
    return;

  // I need to convert through the proxy path.
  QString str = list->currentIndex().data().toString();
  str.replace("(", "."); // Need for QRegExp.
  str.replace(")", ".");
  int row = model->stringList().indexOf(QRegExp(str));
  emit sendSongPath(dir.absolutePath() + "/"
    + filenames.at(row));
}
