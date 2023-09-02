#include "ilbmcreator.h"

#include <fstream>
#include <iostream>

#include <Magick++.h>
#include <QFile>
#include <QImage>
#include <QtDebug>
#include <iostream>
#include <string>

Q_LOGGING_CATEGORY(LOG_ILBM, "com.ilbm-thumb-kde")

extern "C"
{
    Q_DECL_EXPORT ThumbCreator *new_creator()
    {
        return new IlbmCreator();
    }
};

IlbmCreator::IlbmCreator() = default;
IlbmCreator::~IlbmCreator() = default;

bool IlbmCreator::create(const QString &path, int width, int height, QImage &img)
{
    Magick::Image image;
    Magick::Geometry outsize;
    std::string path_string = path.toStdString();
    char aspectx = 0, aspecty = 0;

    int img_size = width * height * 4;
    try
    {
        img_buf = new uchar[img_size];
    }
    catch (...)
    {
        return false;
    }

    /* Extract proper aspect ratio information */
    std::ifstream input(path_string, std::ios::binary);
    if (input.fail())
    {
        return false;
    }
    bool found = false;
    while (!input.eof())
    {
        char tmp;
        input.get(tmp);
        if (tmp == 'B')
        {
            input.get(tmp);
            if (tmp != 'M')
            {
                input.seekg(-1, input.cur);
                continue;
            }
            input.get(tmp);
            if (tmp != 'H')
            {
                input.seekg(-1, input.cur);
                continue;
            }
            input.get(tmp);
            if (tmp != 'D')
            {
                input.seekg(-1, input.cur);
                continue;
            }
            else
            {
                found = true;
                break;
            }
        }
    }
    if (found)
    {
        input.seekg(0x12, input.cur);
        input.get(aspectx);
        input.get(aspecty);
    }
    input.close();
    try
    {
        Magick::Geometry oldsize;
        image.read(path_string);
        oldsize = image.size();
        if (aspectx != aspecty)
        {
            if (aspectx < aspecty)
            {
                oldsize.height(oldsize.height() * aspecty / aspectx);
            }
            else
            {
                oldsize.width(oldsize.width() * aspectx / aspecty);
            }
            oldsize.aspect(true);
            image.scale(oldsize);
        }
        outsize = image.size();
        /* No point in scaling if the image is already smaller than requested */
        if ((int)outsize.width() > width || (int)outsize.height() > height)
        {
            image.scale(Magick::Geometry(width, height));
            outsize = image.size();
        }
        image.write(0, 0, outsize.width(), outsize.height(), "RGBA", Magick::CharPixel, img_buf);
    }
    catch(...)
    {
        return false;
    }
    img = QImage(img_buf,
                 outsize.width(),
                 outsize.height(),
                 QImage::Format_RGBA8888);
    /* Deep copy so we can delete */
    img = img.copy();
    delete[] img_buf;
    return true;
}
