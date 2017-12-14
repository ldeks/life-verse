#include "deck.h"
#include "renderer.h"
#include "mainwindow.h"
#include "song.h"
#include <QApplication>
#include <QUrl>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Renderer r;
    Deck d;
    Song greater;
    greater.loadFromFile("../content/songs/greater");
    d.setSections(greater.toDeckSections());
    r.setHtml(d.genHtml(),
      QUrl::fromLocalFile("/home/laura/programming/life-verse/"));
    r.show();

    MainWindow m;
    m.show();

    return a.exec();
}
