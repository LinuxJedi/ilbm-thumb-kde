#include <iostream>
#include "../ilbmcreator.h"
#include <QImage>
#include <QFile>
#include <Magick++.h>

int main(int argc, char **argv) {
  QImage img;
  IlbmCreator ilmb_creator;

  if (argc != 4)
  {
    std::cout << "Invalid argument count" << std::endl;
    return -1;
  }
  int width = atoi(argv[2]);
  int height = atoi(argv[3]);

  bool result = ilmb_creator.create(argv[1], width, height, img);
  if (!result)
  {
    std::cout << "Error creating thumbnail" << std::endl;
    return -1;
  }
  QFile out_file("test.png");
  out_file.open(QIODevice::WriteOnly);
  img.save(&out_file,"PNG");
  out_file.close();

  /* Test image size */
  Magick::Image image;
  image.read("test.png");
  Magick::Geometry imgsize = image.size();
  if (width > 200 && height > 144)
  {
    if (imgsize.width() != 200 && imgsize.height() != 144)
    {
      std::cout << "Expected 200x144, got " << imgsize.width() << "x" << imgsize.height() << std::endl;
      return -1;
    }
  }
  else
  {
    if (imgsize.width() != width && imgsize.height() != (height * 23 / 32))
    {
      std::cout << "Expected 200x144, got " << imgsize.width() << "x" << imgsize.height() << std::endl;
      return -1;
    }
  }
  std::cout << "Result is " << imgsize.width() << "x" << imgsize.height() << std::endl;

  /* Test we are blue */
  Magick::ColorRGB col = image.pixelColor(0, 0);
  if (col.red() > 0.01 && col.green() > 0.01 && col.blue() < 0.95)
  {
    std::cout << "Unexpectied color: " << col.red() << "," << col.green() << "," << col.blue() << std::endl;
    return -1;
  }

  return 0;
}
