#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QLabel>

class QPixmap;



class ImageView : public QLabel
{
private:
    QPixmap * image;
    QPixmap scaledImage;
    QSize preferedSize;

    void setScaled();
public:
    ImageView(QWidget * parent = 0, Qt::WindowFlags f = 0);
    void setImage(QPixmap * image);

    void setSize(const QSize& size);
protected:
    void paintEvent(QPaintEvent * event);
};

#endif // IMAGEVIEW_H
