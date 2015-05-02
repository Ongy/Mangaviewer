#ifndef PLUGINS_H
#define PLUGINS_H

#include <QString>
#include <QStringList>
#include <QPixmap>

#ifndef APPNAME
#define APPNAME "mangaviewer"
#endif

class ImageProvider
{
public:
    virtual ~ImageProvider() {}

    virtual int loadManga(const QString & name) = 0;
    virtual QStringList getMangas() = 0;
    virtual QString displayChooser() = 0;
    virtual int nextImage(QPixmap * pixmap) = 0;
    virtual int prevImage(QPixmap * pixmap) = 0;
    virtual const QString & getName() const = 0;
};

Q_DECLARE_INTERFACE(ImageProvider, "ongy.mangaviewer.imageprovider")

#endif // PLUGINS_H

