#ifndef FILMSTRIP_H
#define FILMSTRIP_H

#include <QDir>
#include <QImage>
#include <QListView>
#include <QVector>
#include <QStringList>

#include "imagelistmodel.h"

class Filmstrip : public QListView
{
    Q_OBJECT

  public:
    explicit Filmstrip(QWidget *parent = 0);
    ~Filmstrip();

  public slots:
    void serveImageName(const QModelIndex &index);

  signals:
    void imageSelected(const QString &name);

  private:
    QDir dir;
    QStringList fileNames;
    ImageListModel* imgModel;
    QVector<QImage> images;
};

#endif // FILMSTRIP_H
