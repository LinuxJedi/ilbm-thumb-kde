#include "ilbmcreator.h"

#include <Magick++.h>
#include <QFile>
#include <QImage>
#include <QtDebug>
#include <iostream>
#include <string>

Q_LOGGING_CATEGORY(LOG_STL, "com.stl-thumb-kde")

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
    std::string path_string = path.toStdString();
    const char* path_cstring = path_string.c_str();

    int img_size = width * height * 4;
    img_buf = (uchar *) malloc(img_size);
    if (img_buf == NULL) return false;

    try {
        image.read(path_cstring);
        image.scale(Magick::Geometry(width, height));
        image.write(0, 0, width, height, "RGBA", Magick::CharPixel, img_buf);
    }
    catch(...) {
        return false;
    }
    img = QImage(img_buf,
                 width,
                 height,
                 QImage::Format_RGBA8888,
                 (QImageCleanupFunction) &clean,
                 (void*) this);

    return true;
}


void clean(void *info)
{
    IlbmCreator * self = static_cast<IlbmCreator*>(info);
    free(self->img_buf);
}
