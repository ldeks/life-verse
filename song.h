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

private:
  bool hasOpeningTag(QString line, QString tagName = "");
  bool hasClosingTag(QString line, QString tagName = "");
  bool hasSelfClosingTag(QString line, QString tagName = "");
  QStringList readTag(QString line);
  
  QString title;
  QString author;
  QStringList order;
  // Tag string as key, slides in a list as value
  QHash<QString, QStringList> stanzas;
};

#endif // SONG_H
