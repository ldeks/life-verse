#ifndef SONGSLIST_H
#define SONGSLIST_H

#include <QListView>
#include <QMouseEvent>
#include <QFileSystemModel>

class SongsList : public QListView
{
    Q_OBJECT

  public:
    explicit SongsList(QWidget *parent = 0);
    ~SongsList();

  private:
    QFileSystemModel* model;
};

#endif // SONGSLIST_H
