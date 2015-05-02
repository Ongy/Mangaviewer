#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QLabel>

class QPixmap;



class ImageView : public QLabel
{
private:
    QPixmap * image;
    QPixmap scaledImage;
    int Xoffset;
    int Yoffset;

    void setScaled(QSize size);
public:
    ImageView(QWidget * parent = 0, Qt::WindowFlags f = 0);
    void setImage(QPixmap * image);
    void setXoffset(int offset);
    void setYoffset(int offset);

    void adjustXoffset(int offset) { setXoffset(this->Xoffset += offset); }
    void adjustYoffset(int offset) { setYoffset(this->Yoffset += offset); }

    int getXoffset() { return Xoffset; }
    int getYOffset() { return Yoffset; }

    bool isHigh();
protected:
    void paintEvent(QPaintEvent * event);
    void resizeEvent(QResizeEvent * event);
};

#endif // IMAGEVIEW_H
