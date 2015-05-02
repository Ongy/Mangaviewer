#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <QSettings>

#include <stdio.h>
#include "imageprovider.h"


ImageProvider::ImageProvider(QObject *parent)
    : QObject(parent)
    , chapter(1), panel(0)
    , manga("")
{

}

int ImageProvider::loadManga(const QString name)
{
    bool ok;
    this->manga = name;
    QFile info(this->manga + "/.info");
    if(info.open(QIODevice::ReadOnly)) {
        QTextStream in(&info);
        while(!in.atEnd()) {
            QString line = in.readLine();
            this->chapters.append(line.toInt(&ok));
            if(!ok) {
                qDebug("Could not convert %s int a number", line.toStdString().c_str());
                return -1;
            }
        }
    }
    else {
        qDebug("Could not find info file");
        return -1;
    }
    QSettings settings(NULL);
    settings.beginGroup("provider/file");
    settings.beginGroup(this->manga);
    this->chapter = settings.value("chapter", 1).toInt();
    this->panel = settings.value("panel", 0).toInt();
    settings.endGroup();
    settings.endGroup();
    return 0;
}

QString ImageProvider::getPath()
{
    char buffer[128];
    QString path = this->manga;
    snprintf(buffer, sizeof(buffer), "/%d/%d.jpg", this->chapter, this->panel);
    path.append(buffer);
    return path;
}

int ImageProvider::nextImage(QPixmap * pixmap)
{
    int tmp = this->panel;
    if(++this->panel > this->chapters[this->chapter -1]) {
        this->panel = 1;
        if(++this->chapter > this->chapters.length()) {
            --this->chapter;
            this->panel = tmp;
            return -1;
        }
    }

    QString path = getPath();
    new(pixmap) QPixmap(path);
    return 0;
}

int ImageProvider::prevImage(QPixmap *pixmap)
{
    if(this->backOff() < 0)
        return -1;
    QString path = getPath();
    new(pixmap) QPixmap(path);
    return 0;
}

int ImageProvider::backOff()
{
    if(!--this->panel) {
        if(!--this->chapter) {
            this->panel = 1;
            this->chapter = 1;
            return -1;
        }
        this->panel = this->chapters[this->chapter-1];
    }
    return 0;
}

ImageProvider::~ImageProvider()
{
    this->backOff();
    QSettings settings(NULL);
    settings.beginGroup("provider/file");
    settings.beginGroup(this->manga);
    settings.setValue("chapter", this->chapter);
    settings.setValue("panel", this->panel);
    settings.endGroup();
    settings.endGroup();
}
