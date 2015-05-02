#include <QGraphicsPixmapItem>
#include <QResizeEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QFileDialog>
#include <QDir>
#include <QSettings>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QInputDialog>

#include "mangaviewer.h"
#include "ui_mangaviewer.h"

#include "config.h"

MangaViewer::MangaViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MangaViewer),
    provider(NULL),
    image(new QPixmap())
{
    ui->setupUi(this);

    QSettings settings(APPNAME, "mangaviewer");
    settings.beginGroup("viewer");
    this->hscroll = settings.value("hscroll", -1).toInt();
    if(this->hscroll == -1) {
        this->hscroll = HSCROLL;
        settings.setValue("hscroll", this->hscroll);
    }
    this->vscroll = settings.value("vscroll", -1).toInt();
    if(this->vscroll == -1) {
        this->vscroll = VSCROLL;
        settings.setValue("vscroll", this->vscroll);
    }
    settings.endGroup();
    this->defaultProvider = settings.value("provider/default", "").toString();
    if(this->defaultProvider == "") {
        this->defaultProvider = DEFAULT_PROVIDER;
        settings.setValue("provider/default", this->defaultProvider);
    }
}

MangaViewer::~MangaViewer()
{
    delete ui;
}

void MangaViewer::resizeEvent(QResizeEvent * event)
{
    ui->label->setSize(event->size());
}

void MangaViewer::loadManga()
{
    if(!this->provider)
        this->provider = this->collection.getPlugin(this->defaultProvider);

    if(!this->provider) {
        qDebug("Could not load default provider");
        return;
    }

    QString manga;
    QStringList list = this->provider->getMangas();
    if(list.empty()) {
        manga = this->provider->displayChooser();
    } else {
        manga = "";
    }

    if(provider->loadManga(manga) < 0) {
        return;
    }
    loadNextFile();

    if(FULLSCREEN)
        this->showFullScreen();
}

void MangaViewer::postFileLoad()
{
    ui->scrollArea->horizontalScrollBar()->setValue(0);
    ui->scrollArea->verticalScrollBar()->setValue(0);
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
    QPropertyAnimation * anim = NULL;
    switch(event->key()) {
    case Qt::Key_Left:
        if(ui->label->width() <= this->width() || event->modifiers() & Qt::ShiftModifier) {
            loadPrevFile();
        }
        else {
            anim = new QPropertyAnimation(ui->scrollArea->horizontalScrollBar(), "value");
            anim->setEndValue(ui->scrollArea->horizontalScrollBar()->value() - this->hscroll);
        }
        break;
    case Qt::Key_Right:
        if(ui->label->width() <= this->width() || event->modifiers() & Qt::ShiftModifier) {
            loadNextFile();
        }
        else{
            anim = new QPropertyAnimation(ui->scrollArea->horizontalScrollBar(), "value");
            anim->setEndValue(ui->scrollArea->horizontalScrollBar()->value() + this->hscroll);
        }
        break;
    case Qt::Key_Up:
        anim = new QPropertyAnimation(ui->scrollArea->verticalScrollBar(), "value");
        anim->setEndValue(ui->scrollArea->verticalScrollBar()->value() - this->vscroll);
        break;
    case Qt::Key_Down:
        anim = new QPropertyAnimation(ui->scrollArea->verticalScrollBar(), "value");
        anim->setEndValue(ui->scrollArea->verticalScrollBar()->value() + this->vscroll);
        break;
    case Qt::Key_F5:
        this->showFullScreen();
        break;
    case Qt::Key_Escape:
        this->showNormal();
        break;
    case Qt::Key_O:
        if(event->modifiers() & Qt::ControlModifier) {
            QString plugin = QInputDialog::getItem(this, "Choose image provider", "Providers:",
                                                   this->collection.getPluginList(), 0, false);
            if(plugin == "")
                return;
            this->provider = this->collection.getPlugin(plugin);
        }
        this->loadManga();
        break;
    case Qt::Key_Q:
        QApplication::quit();
        break;
    default:
        event->ignore();
    }
    if(anim)
        anim->start(QAbstractAnimation::DeleteWhenStopped);
}
