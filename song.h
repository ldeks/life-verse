#ifndef SONG_H
#define SONG_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QHash>

class Song : public QObject
{
    Q_OBJECT

public:
  explicit Song(QObject *parent = 0);
  ~Song();

  bool loadFromFile(QString filename);
  //QStringList toDeckSections();
  QString getTitle() { return title; }
  QString getAuthor() { return author; }
  QStringList getOrder() { return order; }
  QStringList getStanzas(QString key);

private:
  bool hasOpeningTag(QString line, QString tagName = "");
  bool hasClosingTag(QString line, QString tagName = "");
  QString readTagContents(QString line);
  bool hasSelfClosingTag(QString line, QString tagName = "");
  QString getSelfClosingTag(QString line);
  
  QString title;
  QString author;
  QStringList order;
  // Tag string as key, slides in a list as value
  QHash<QString, QStringList> stanzas;
};

#endif // SONG_H
