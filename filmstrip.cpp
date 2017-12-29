#include "filmstrip.h"

Filmstrip::Filmstrip(QWidget *parent) :
    QListView(parent)
{
  model = new QStringListModel(this);
  setModel(model);
  setFlow(QListView::LeftToRight);
  setUniformItemSizes(true);

  dir = QDir("../content/images/");
  model->setStringList(dir.entryList(QDir::Files));
}

Filmstrip::~Filmstrip()
{
}
