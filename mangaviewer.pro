#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T08:32:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mangaviewer
TEMPLATE = app


SOURCES += main.cpp\
        mangaviewer.cpp \
    imageview.cpp \
    imageprovider.cpp

HEADERS  += mangaviewer.h \
    imageview.h \
    imageprovider.h \
    config.h

FORMS    += mangaviewer.ui

RESOURCES +=
