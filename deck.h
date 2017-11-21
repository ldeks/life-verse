#ifndef DECK_H
#define DECK_H

#include <QColor>
#include <QObject>
#include <QString>
#include <QStringList>

class Deck : public QObject
{
    Q_OBJECT

public:
  explicit Deck(QObject *parent = 0);
  ~Deck();

  void setTransition(QString tr);
  QString genHtml(); // No caching for now.
  void writeFile();
  void setSections(QStringList text);

private:
  QString filename;
  QColor fontColor;
  QString fontFamily;
  int fontSize;
  QString fontUnit;
  float opacity;
  QString stillLink;
  QString videoLink;
  QStringList sections;
  QString transition;
  QStringList validTransitions;
};

#endif // DECK_H
