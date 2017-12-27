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
  QStringList toDeckSections();
  QStringList toLyricSections(); // unrolled
  QStringList getLyricOrder(); // unrolled
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
  QString getKey(QString orderCode);
  
  QString title;
  QString author;
  QStringList order;
  // Tag string as key, slides in a list as value
  QHash<QString, QStringList> stanzas;
  // A translation table for the order mini language.
  // E.g. "v" as key, "verse" as value
  QHash<QString, QString> orderToTagName;
};

#endif // SONG_H
