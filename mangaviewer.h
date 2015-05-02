#ifndef MANGAVIEWER_H
#define MANGAVIEWER_H

#include <QMainWindow>
#include <QString>

#include "imageprovider.h"

namespace Ui {
class MangaViewer;
}

class MangaViewer : public QMainWindow
{
    Q_OBJECT
    Ui::MangaViewer *ui;
    ImageProvider * provider;
    QPixmap * image;

    int hscroll;
    int vscroll;

public:
    explicit MangaViewer(QWidget *parent = 0);
    ~MangaViewer();

protected:
    void keyPressEvent(QKeyEvent * event);

private:

    void loadNextFile();
    void loadPrevFile();
    void loadManga(QString & manga);
};

#endif // MANGAVIEWER_H
