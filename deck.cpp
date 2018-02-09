#include "deck.h"
#include <QFile>
#include <QTextStream>

Deck::Deck(QObject *parent) :
    QObject(parent)
{
  filename = "../out.html";
  fontColor.setRgb(245, 245, 245);
  fontFamily = "Quicksand";
  fontSize = 100;
  fontUnit = "px";
  fontWeight = "500";
  textShadowString = "2px 2px 8px #303030";
  opacity = 0.8;
  stillLink = "content/images/geo5.jpg";
  sections.append("Say something meaningful<br>with Life Verse.");
  sections.append("It's all you need<br>and nothing more.");
  sections.append("With no artificial features<br>or premature optimizations.");
  validTransitions << "none" << "fade" << "slide" << "convex" << "concave"
                   << "zoom";
  transition = validTransitions.at(1);
}

Deck::~Deck()
{
}

void
Deck::setTransition(QString tr) {
  // If this fails, you silently get fade. Cry in agony.
  if (validTransitions.contains(tr, Qt::CaseInsensitive)) {
    transition = tr.toLower();
  }
}

QString
Deck::genHtml() {
  QString ret;
  QTextStream out(&ret);

  // Common "header" stuff.
  out << "<!DOCTYPE html>\n"
      << "<html>\n"
      << "<head>\n"
      << "  <link rel=\"stylesheet\" href=\"reveal.js/css/reveal.css\">\n"
      << "  <link rel=\"stylesheet\" href=\"reveal.js/css/theme/black.css\">\n"
      << "  <style>\n"
      << "    .reveal {\n"
      << "   font-family: \"" << fontFamily << "\", sans-serif;\n"
      << "   font-size: " << fontSize << fontUnit << ";\n"
      << "   color: rgb(" << fontColor.red() << ", " << fontColor.green() << ", " << fontColor.blue() << ");\n"
      << "   opacity: " << opacity << ";\n"
      << "   font-weight: " << fontWeight << ";\n"
      << "   text-shadow: " << textShadowString << ";\n"
      << "}\n"
      // Need this section so video spans whole view.
      // reveal.js themes set this to 95%.
      << ".reveal img,\n"
      << ".reveal video,\n"
      << ".reveal iframe {\n"
      << "  max-width: 100%;\n"
      << "  max-height: 100%; }\n"
      << "  </style>\n"
      << "  <title>Reveal.js Lyrics</title>\n"
      << "</head>\n"
      << "\n"
      << "<body>\n"
      << "  <div class=\"reveal\">\n"
      << "    <div class=\"slides\">\n";

  // Video background stuff.
  if (!videoLink.isEmpty()) {
    out <<  "      <video width=\"1600\" height=\"900\" autoplay loop>\n"
        <<  "        <source src=\"" << videoLink << "\" type=\"video/mp4\">\n"
        <<  "      </video>\n";
  }

  if (!stillLink.isEmpty()) {
    out <<  "      <img width=\"1600\" height=\"900\" src=\"" << stillLink <<"\"/>\n";
  }
  
  // Text section stuff.
  for (int i = 0; i < sections.length(); i++) {
     //TODO: Handle <br> properly.
     out << "      <section>\n"
         << "         " << sections[i] << "\n"
         << "      </section>\n";
  }

  // Controls and "footer" stuff.
  out << "    </div>\n"
      << "  </div>\n"
      << "  <script src=\"reveal.js/js/reveal.js\"></script>\n"
      << "  <script>\n"
      << "    Reveal.initialize({\n"
      << "      controls: false,\n"
      << "      progress: false,\n"
      << "      transition: '" << transition << "',\n"
      << "      width: 1600,\n" // Need this to specify desired aspect ratio
      << "      height: 900,\n"
      << "      margin: 0.0,\n" // Need this to specify no border.
      << "      });\n"
      << "  </script>\n"
      << "</body>\n";
  out << "</html>";

  return ret;
}

void
Deck::writeFile() {
  QFile file (filename);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;

  QTextStream out(&file);

  out << genHtml();

  file.close();
}

void
Deck::setSections(QStringList text) {
  sections = text;
}

int
Deck::getFontShadowSize()
{
  QString shadowSize = textShadowString.split(" ").at(0);
  int unitLoc = 2;
  if (shadowSize.contains("rem"))
    unitLoc = 3;
  return shadowSize.left(shadowSize.size() - unitLoc).toInt();
}
