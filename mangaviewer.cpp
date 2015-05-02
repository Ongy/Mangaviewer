#include <QGraphicsPixmapItem>
#include <QResizeEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QFileDialog>
#include <QDir>
#include <QSettings>

#include "mangaviewer.h"
#include "ui_mangaviewer.h"
#include "imageprovider.h"

#include "config.h"

MangaViewer::MangaViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MangaViewer),
    provider(new ImageProvider(this)),
    image(new QPixmap())
{
    ui->setupUi(this);

    QSettings settings(NULL);
    settings.beginGroup("viewer");
    this->hscroll = settings.value("hscroll", HSCROLL).toInt();
    this->vscroll = settings.value("vscroll", VSCROLL).toInt();
    settings.endGroup();
}

MangaViewer::~MangaViewer()
{
    delete ui;
}

void MangaViewer::loadManga(QString & manga)
{
    if(provider->loadManga(manga) < 0) {
        return;
    }
    loadNextFile();

    if(FULLSCREEN)
        this->showFullScreen();
}

void MangaViewer::loadNextFile()
{
    if(this->provider->nextImage(image) < 0) {
        qDebug("Provider could not provide a next file");
        return;
    }
    if(image->isNull())
        qDebug("Image was null");
    else
        ui->label->setImage(image);
}

void MangaViewer::loadPrevFile()
{
    if(this->provider->prevImage(image) < 0) {
        qDebug("Provider could not provide a previous file");
        return;
    }
    if(image->isNull())
        qDebug("Image was null");
    else
        ui->label->setImage(image);
}

void MangaViewer::keyPressEvent(QKeyEvent * event)
{
    switch(event->key()) {
    case Qt::Key_Left:
        if(ui->label->isHigh() || event->modifiers() & Qt::ShiftModifier)
            loadPrevFile();
        else
            ui->label->adjustXoffset(-this->hscroll);
        break;
    case Qt::Key_Right:
        if(ui->label->isHigh() || event->modifiers() & Qt::ShiftModifier)
            loadNextFile();
        else
            ui->label->adjustXoffset(this->hscroll);
        break;
    case Qt::Key_Up:
        ui->label->adjustYoffset(-this->vscroll);
        break;
    case Qt::Key_Down:
        ui->label->adjustYoffset(this->vscroll);
        break;
    case Qt::Key_F5:
        this->showFullScreen();
        break;
    case Qt::Key_Escape:
        this->showNormal();
        break;
    case Qt::Key_O:
        if(event->modifiers() & Qt::ControlModifier){
            QString home = QDir::homePath();
            QString manga = QFileDialog::getExistingDirectory(this, "Choose which manga to view", home);
            this->loadManga(manga);
        }
        break;
    case Qt::Key_Q:
        QApplication::quit();
        break;
    default:
        event->ignore();
    }
}
