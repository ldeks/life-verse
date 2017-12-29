#ifndef FILMSTRIP_H
#define FILMSTRIP_H

#include <QDir>
#include <QListView>
#include <QStringList>
#include <QStringListModel>

class Filmstrip : public QListView
{
    Q_OBJECT

  public:
    explicit Filmstrip(QWidget *parent = 0);
    ~Filmstrip();

  private:
    QDir dir;
    QStringList stringList;
    QStringListModel* model;
};

#endif // FILMSTRIP_H
