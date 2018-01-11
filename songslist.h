#ifndef SONGSLIST_H
#define SONGSLIST_H

#include <QDir>
#include <QListView>
#include <QMouseEvent>
#include <QMimeData>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QStringList>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QWidget>

class SongsListModel:  public QStringListModel
{
    Q_OBJECT

  public:
    explicit SongsListModel(QWidget *parent = 0);
    ~SongsListModel();

    void setFilePath(QString fpath) { path = fpath; }
    void setFileNames(QStringList names) { fileNames = names; }

    QMimeData* mimeData(const QModelIndexList &indexes) const;

  private:
    QString path;
    QStringList fileNames;
};

class SongsList : public QWidget
{
    Q_OBJECT

  public:
    explicit SongsList(QWidget *parent = 0);
    ~SongsList();

  private:
    QDir dir;
    QVBoxLayout* vLayout;
    QListView* list;
    QSortFilterProxyModel* proxyModel;
    SongsListModel* model;
    QStringList filenames;
    QLineEdit* filter;
};

#endif // SONGSLIST_H
