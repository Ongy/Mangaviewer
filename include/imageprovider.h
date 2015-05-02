#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QObject>
#include <QString>
#include <QList>

class ImageProvider : public QObject
{
    Q_OBJECT
    QList<int> chapters;
    QString getPath();
    int backOff();
protected:
    int chapter;
    int panel;
    QString manga;
    QString path;
public:
    ImageProvider(QObject *parent = 0);
    int loadManga(const QString name);
    virtual int nextImage(QPixmap * pixmap);
    virtual int prevImage(QPixmap * pixmap);
    ~ImageProvider();
signals:

public slots:
};

#endif // IMAGEPROVIDER_H
