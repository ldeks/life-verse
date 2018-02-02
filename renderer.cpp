#include "renderer.h"
#include <QCoreApplication>

Renderer::Renderer(QWidget *parent) :
    QWidget(parent)
{
  layout = new QVBoxLayout(this);
  setLayout(layout);
  layout->setContentsMargins(0, 0, 0, 0);
}

Renderer::~Renderer()
{
  QCoreApplication::quit();
}

void
Renderer::closeEvent(QCloseEvent* e) {
  QCoreApplication::quit();
}
