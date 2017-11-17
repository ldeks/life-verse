#include "song.h"
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

Song::Song(QObject *parent) :
    QObject(parent)
{
}

Song::~Song()
{
}

bool
Song::loadFromFile(QString filename) {
  QFile file (filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  QTextStream in(&file);

  // Verify header. Magic string for now.
  QString header;
  if (!in.readLineInto(&header))
    return false;
  if (header != "<!DOCTYPE life-verse-markup-language-0.1/>")
    return false;

  // Read contents.
  while (!in.atEnd()) {
    QString line = in.readLine();

    // Look for opening tag.
    if (!hasOpeningTag(line))
      continue; // Didn't have a tag.

    if (hasOpeningTag(line, "title") {
      while ((!in.atEnd() && (!hasClosingTag(line, "title"))) {
        line += in.readLine();
      }
      title = readTag(line).at(0);
    }
    else if (hasOpeningTag(line, "author")) {
      while ((!in.atEnd() && (!hasClosingTag(line, "author"))) {
        line += in.readLine();
      }
      author = readTag(line).at(0);
   }
   else if (hasOpeningTag(line, "order")) {
      while ((!in.atEnd() && (!hasClosingTag(line, "order"))) {
        line += in.readLine();
      }
      QString orderLine = readTag(line).at(0);
      order = orderLine.split(QRegularExpression("/\s*,\s*/");
   }
   else if (hasSelfClosingTag(line)) {
      // TODO: Read until next self closing tag.
   }
  }

  file.close();
}

bool
Song::hasOpeningTag(QString line, QString tagName) {
  QString regSeed;
  regSeed += "/<\s*";
  if (tagName.isEmpty())
    regSeed += "[\w|\s]*";
  else
    regSeed += tagName;

  regSeed += "\s*>/i";

}

bool
Song::hasClosingTag(QString line, QString tagName) {
  QString regSeed;
  regSeed += "/<\\\s*";
  if (tagName.isEmpty())
    regSeed += "[\w|\s]*";
  else
    regSeed += tagName;

  regSeed += "\s*>/i";

  return line.contains(QRegularExpression(regSeed));
}

bool
Song::hasSelfClosingTag(QString line, QString tagName) {
  QString regSeed;
  regSeed += "/<\s*";
  if (tagName.isEmpty())
    regSeed += "[\w|\s]*";
  else
    regSeed += tagName;

  regSeed += "\s*\\>/i";

  return line.contains(QRegularExpression(regSeed));
}

QStringList
Song::readTag(QString line) {

      return line.split(QRegularExpression("/<\\?\s*[\w|\s]*\s*>/i"));
}
