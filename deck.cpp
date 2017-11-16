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
  opacity = 0.8;
  sections.append("Say something meaningful....");
  sections.append("with Life Verse.");
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

void
Deck::writeFile() {
  QFile file (filename);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;

  QTextStream out(&file);

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
      << "}\n"
      << "  </style>\n"
      << "  <title>Reveal.js Lyrics</title>\n"
      << "</head>\n"
      << "\n"
      << "<body>\n"
      << "  <div class=\"reveal\">\n"
      << "    <div class=\"slides\">\n";

  // TODO: Video background stuff.
        //<video width="1600" height="900" autoplay loop>
        //  <source src="https://player.vimeo.com/external/188557098.hd.mp4?s=911c1c900d991c43cec89ed87bd2578ca7060d4c&profile_id=174&oauth2_token_id=57447761" type="video/mp4">

        //  Your browser does not support the video tag.
        //</video>
  
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
      << "      width: 1600,\n"
      << "      height: 900,\n"
      << "      });\n"
      << "  </script>\n"
      << "</body>\n";
  out << "</html>";

  file.close();
}
