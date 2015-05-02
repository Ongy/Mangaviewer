#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>

#include "imageview.h"

ImageView::ImageView(QWidget * parent, Qt::WindowFlags f)
    : QLabel(parent, f),
      Xoffset(0), Yoffset(0)
{

}


void ImageView::paintEvent(QPaintEvent * event)
{
    if(this->image) {
        QPainter painter(this);
        QRect rect = this->rect();
        rect.translate(Xoffset, Yoffset);
        painter.drawPixmap(this->rect(), this->scaledImage, rect);
    }
    event->ignore();
}

void ImageView::resizeEvent(QResizeEvent * event)
{
    this->setScaled(event->size());
    this->setXoffset(0);
    this->setYoffset(0);
}

void ImageView::setXoffset(int offset)
{
    this->Xoffset = offset;
    if(this->Xoffset < 0)
        this->Xoffset = 0;
    if(this->Xoffset + this->width() > this->scaledImage.width())
        this->Xoffset = this->scaledImage.width() - this->width();
    this->update();
}

void ImageView::setYoffset(int offset)
{
    this->Yoffset = offset;
    if(this->Yoffset < 0)
        this->Yoffset = 0;
    if(this->Yoffset + this->height() > this->scaledImage.height())
        this->Yoffset = this->scaledImage.height() - this->height();
    this->update();
}

void ImageView::setImage(QPixmap *image)
{
    this->image = image;
    this->setScaled(this->size());
    this->setXoffset(0);
    this->setYoffset(0);
}

void ImageView::setScaled(QSize size)
{
    if(this->image)
        this->scaledImage = this->image->scaled(size,
                                            Qt::KeepAspectRatioByExpanding,
                                            Qt::SmoothTransformation);
}

bool ImageView::isHigh()
{
    if(!this->image)
        return false;
    return this->scaledImage.width() == this->width();
}
