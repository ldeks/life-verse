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

  enum TransitionType {none, fade, slide, convex, concave, zoom};

  void writeFile();

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
  TransitionType transition;
};

#endif // DECK_H
