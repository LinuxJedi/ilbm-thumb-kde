#include "ilbmcreator.h"

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

    int img_size = width * height * 4;
    try
    {
        img_buf = new uchar[img_size];
    }
    catch (...)
    {
        return false;
    }

    try
    {
        image.read(path_string);
        image.scale(Magick::Geometry(width, height));
        outsize = image.size();
        image.write(0, 0, outsize.width(), outsize.height(), "RGBA", Magick::CharPixel, img_buf);
    }
    catch(...)
    {
        return false;
    }
    img = QImage(img_buf,
                 outsize.width(),
                 outsize.height(),
                 QImage::Format_RGBA8888,
                 (QImageCleanupFunction) &clean,
                 (void*) this);

    return true;
}


void clean(void *info)
{
    IlbmCreator * self = static_cast<IlbmCreator*>(info);
    delete[] self->img_buf;
}
