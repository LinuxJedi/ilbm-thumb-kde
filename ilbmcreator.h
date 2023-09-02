#pragma once

#include <KIO/ThumbnailCreator>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(LOG_ILBM)

class IlbmCreator : public KIO::ThumbnailCreator
{
        Q_OBJECT
    public:
        IlbmCreator(QObject *parent, const QVariantList &args);
        ~IlbmCreator() override;

        KIO::ThumbnailResult create(const KIO::ThumbnailRequest &request) override;

        uchar *img_buf = NULL;
};
