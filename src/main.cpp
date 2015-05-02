#include "mangaviewer.h"
#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MangaViewer w;
    w.show();
//    QCoreApplication::setOrganizationName("mangaviewer");
//    QCoreApplication::setApplicationName("Mangaviewer");

    return a.exec();
}
