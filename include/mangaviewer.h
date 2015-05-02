#ifndef MANGAVIEWER_H
#define MANGAVIEWER_H

#include <QMainWindow>
#include <QString>

#include "providercollection.h"
#include "mangaviewer/plugins.h"

namespace Ui {
class MangaViewer;
}

class MangaViewer : public QMainWindow
{
    Q_OBJECT
    Ui::MangaViewer *ui;
    ProviderCollection collection;
    ImageProvider * provider;
    QPixmap * image;
    QString defaultProvider;

    int hscroll;
    int vscroll;

public:
    explicit MangaViewer(QWidget *parent = 0);
    ~MangaViewer();

protected:
    void keyPressEvent(QKeyEvent * event);
    void resizeEvent(QResizeEvent * event);

private:

    void postFileLoad();
    void loadNextFile();
    void loadPrevFile();
    void loadManga();
};

#endif // MANGAVIEWER_H
