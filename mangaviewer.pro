#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T08:32:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mangaviewer
TEMPLATE = app

INCLUDEPATH += include

SOURCES += src/main.cpp\
        src/mangaviewer.cpp \
    src/imageview.cpp \
    src/providercollection.cpp

HEADERS  += include/mangaviewer.h \
    include/imageview.h \
    include/config.h \
    include/mangaviewer/plugins.h \
    include/providercollection.h

FORMS    += resources/mangaviewer.ui

RESOURCES +=
