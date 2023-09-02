#pragma once

#include <KIO/ThumbCreator>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(LOG_ILBM)

class IlbmCreator : public ThumbCreator
{
    public:
        IlbmCreator();
        ~IlbmCreator() override;
        bool create(const QString &path, int width, int height, QImage &img) override;

        uchar *img_buf = NULL;
};
