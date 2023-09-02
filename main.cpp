#include <iostream>
#include "ilbmcreator.h"
#include <QImage>
#include <QFile>

int main(int argc, char **argv) {
  QImage img;
  const QString fn("test.iff");
  IlbmCreator ilmb_creator;

  ilmb_creator.create(fn,128,128,img);
  QFile out_file("test.png");
  out_file.open(QIODevice::WriteOnly);
  img.save(&out_file,"PNG");
  out_file.close();

  return 0;
}
