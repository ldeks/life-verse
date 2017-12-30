#ifndef IMAGELISTMODEL_H
#define IMAGELISTMODEL_H

#include <QAbstractListModel>
#include <QImage>
#include <QVector>

class ImageListModel : public QAbstractListModel
{
    Q_OBJECT

  public:
    explicit ImageListModel(QObject *parent = 0);
    ~ImageListModel();

    void setImages(const QVector<QImage>& imgs) { images = imgs; }

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  private:
    QVector<QImage> images;
};

#endif // IMAGELISTMODEL_H
