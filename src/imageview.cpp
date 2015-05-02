#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>

#include "imageview.h"

ImageView::ImageView(QWidget * parent, Qt::WindowFlags f)
    : QLabel(parent, f)
{

}


void ImageView::paintEvent(QPaintEvent * event)
{
    if(this->image) {
        QPainter painter(this);
        painter.drawPixmap(this->rect(), this->scaledImage, this->rect());
    }
    event->accept();
}

void ImageView::setSize(const QSize &size)
{
    this->preferedSize = size;
    this->setScaled();
}

void ImageView::setImage(QPixmap *image)
{
    this->image = image;
    this->setScaled();
}

void ImageView::setScaled()
{
    if(!this->image)
        return;
    this->scaledImage = this->image->scaled(this->preferedSize,
                                            Qt::KeepAspectRatioByExpanding,
                                            Qt::SmoothTransformation);
    this->setFixedSize(this->scaledImage.size());
}
