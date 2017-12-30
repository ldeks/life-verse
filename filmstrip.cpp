#include "filmstrip.h"

#include <QStringList>

Filmstrip::Filmstrip(QWidget *parent) :
    QListView(parent)
{
  setFlow(QListView::LeftToRight);
  setUniformItemSizes(true);
  setIconSize(QSize(250, 141));
  setMaximumHeight(150);

  dir = QDir("../content/images/");
  QStringList imgExts;
  imgExts << "*.png" << "*.jpg" << "*.jpeg";
  QStringList stringList = dir.entryList(imgExts);

  for (int i = 0; i < stringList.size(); i++) {
    QImage img (dir.filePath(stringList.at(i)));
    images.append(img.scaledToWidth(250));
  }

  imgModel = new ImageListModel(this);
  imgModel->setImages(images);
  setModel(imgModel);
}

Filmstrip::~Filmstrip()
{
}
