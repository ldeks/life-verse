#ifndef SONGSLIST_H
#define SONGSLIST_H

#include <QListView>
#include <QMouseEvent>
#include <QFileSystemModel>
#include <QVBoxLayout>
#include <QWidget>

class SongsList : public QWidget
{
    Q_OBJECT

  public:
    explicit SongsList(QWidget *parent = 0);
    ~SongsList();

  private:
    QVBoxLayout* vLayout;
    QListView* list;
    QFileSystemModel* model;
};

#endif // SONGSLIST_H
