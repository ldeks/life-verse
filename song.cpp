#include "song.h"
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

Song::Song(QObject *parent) :
    QObject(parent)
{
  // Build the translation table for order.
  orderToTagName["v"] = "verse";
  orderToTagName["c"] = "chorus";
  orderToTagName["p"] = "pre-chorus";
  orderToTagName["e"] = "ending";
  orderToTagName["i"] = "intro";
  orderToTagName["b"] = "bridge";
  orderToTagName["o"] = "outro";
}

Song::~Song()
{
}

QStringList
Song::getStanzas(QString key) {
  if (stanzas.contains(key))
    return stanzas.value(key);
  else
    return QStringList();
}

bool
Song::loadFromFile(QString filename) {
  QFile file (filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return false;

  QTextStream in(&file);

  // Verify header. Magic string for now.
  QString header;
  if (!in.readLineInto(&header))
    return false;
  if (header != "<!DOCTYPE life-verse-markup-language-0.1/>")
    return false;

  // Read contents.
  QString currentStanza;
  QString currentSelfClosingTag;

  while (!in.atEnd()) {
    QString line = in.readLine();

    if (hasOpeningTag(line, "title")) {
      while ((!in.atEnd() && (!hasClosingTag(line, "title")))) {
        line += in.readLine();
      }
      title = readTagContents(line);
    }
    else if (hasOpeningTag(line, "author")) {
      while ((!in.atEnd() && (!hasClosingTag(line, "author")))) {
        line += in.readLine();
      }
      author = readTagContents(line);
   }
   else if (hasOpeningTag(line, "order")) {
      while ((!in.atEnd() && (!hasClosingTag(line, "order")))) {
        line += in.readLine();
      }
      QString orderLine = readTagContents(line).toLower();
      order = orderLine.split(QRegularExpression("\\s*,\\s*"));
   }
   else if (hasSelfClosingTag(line)) {
      // Flush old stanza.
      if (!currentSelfClosingTag.isNull()) {
        stanzas[currentSelfClosingTag].append(currentStanza.trimmed());
        currentStanza = QString();
      }

      if (getSelfClosingTag(line) != currentSelfClosingTag) {
        // New section.
        currentSelfClosingTag = getSelfClosingTag(line);
      }
   }
   else if (!currentSelfClosingTag.isNull()) {
      // Must be in the middle of filling a stanza.
      // Trim and add fresh new-line to avoid extra whitespace on screen.
      currentStanza += line.trimmed() + "\n";
   }
  }

  //Flush any remaining data.
  if (!currentSelfClosingTag.isNull())
    stanzas[currentSelfClosingTag].append(currentStanza.trimmed());

  file.close();

  return true;
}

bool
Song::hasOpeningTag(QString line, QString tagName) {
  QString regSeed;
  regSeed += "<\\s*";
  if (tagName.isEmpty())
    regSeed += "[\\w|\\s]*";
  else
    regSeed += tagName;

  regSeed += "\\s*>";

  return line.contains(QRegularExpression(regSeed,
    QRegularExpression::CaseInsensitiveOption));
}

bool
Song::hasClosingTag(QString line, QString tagName) {
  QString regSeed;
  regSeed += "<\\/\\s*";
  if (tagName.isEmpty())
    regSeed += "[\\w|\\s]*";
  else
    regSeed += tagName;

  regSeed += "\\s*>";

  return line.contains(QRegularExpression(regSeed,
    QRegularExpression::CaseInsensitiveOption));
}

bool
Song::hasSelfClosingTag(QString line, QString tagName) {
  QString regSeed;
  regSeed += "<\\s*";
  if (tagName.isEmpty())
    regSeed += "[\\w|\\s|-]*";
  else
    regSeed += tagName;

  regSeed += "\\s*\\/>";

  return line.contains(QRegularExpression(regSeed,
    QRegularExpression::CaseInsensitiveOption));
}

QString
Song::readTagContents(QString line) {
  return line.split(QRegularExpression("<\\/?\\s*[\\w|\\s]*\\s*>"),
    QString::SkipEmptyParts).at(0);
}

QString
Song::getSelfClosingTag(QString line) {
  return line.split(QRegularExpression("\\s*[<|\\/]>?\\s*"),
    QString::SkipEmptyParts).at(0).toLower();
}

QStringList
Song::toDeckSections() {
  QStringList ret = toLyricSections();
  for (int i = 0; i < ret.size(); i++) {
    ret[i] = ret[i].replace("\n", "<br>");
  }
  return ret;
}

QString
Song::getKey(QString orderCode)
{
  QString numberPart = orderCode.mid(1);
  return orderToTagName[orderCode.left(1)] + " " + numberPart;
}

QStringList
Song::toLyricSections() {
  QStringList ret;

  for (int i = 0; i < order.size(); i++) {
    if ((order.at(i) == "solo") || (order.at(i) == "s")) {
      ret << "";
    }
    else {
      QString key = getKey(order.at(i));
      if (stanzas.contains(key)) {
        ret << stanzas[key];
      }
    }
  }

  return ret;
}

QStringList
Song::getLyricOrder()
{
  QStringList ret;

  for (int i = 0; i < order.size(); i++) {
    if ((order.at(i) == "solo") || (order.at(i) == "s")) {
      ret << "solo";
    }
    else {
      QString key = getKey(order.at(i));
      if (stanzas.contains(key)) {
        for (int j = 0; j < stanzas[key].size(); j++) {
          ret << order.at(i);
        }
      }
    }
  }

  return ret;
}
