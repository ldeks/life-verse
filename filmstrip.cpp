#include "filmstrip.h"

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
  fileNames = dir.entryList(imgExts);

  for (int i = 0; i < fileNames.size(); i++) {
    QImage img (dir.filePath(fileNames.at(i)));
    images.append(img.scaledToWidth(250));
  }

  imgModel = new ImageListModel(this);
  imgModel->setImages(images);
  setModel(imgModel);
}

Filmstrip::~Filmstrip()
{
}
