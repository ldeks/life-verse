#include "imagelistmodel.h"

#include <QIcon>
#include <QPixmap>

ImageListModel::ImageListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

ImageListModel::~ImageListModel()
{
}

int
ImageListModel::rowCount(const QModelIndex& parent) const
{
  if (parent.isValid())
      return 0;
  else
      return images.size();
}

QVariant
ImageListModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
      return QVariant();

  if (role == Qt::DecorationRole)
    return QIcon(QPixmap::fromImage(images.at(index.row())));

  return QVariant();
}
