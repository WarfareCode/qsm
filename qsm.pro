#-------------------------------------------------
#
# Project created by QtCreator 2011-01-15T13:50:11
#
#-------------------------------------------------

QT += core gui opengl xml

TARGET = qsm
TEMPLATE = app


HEADERS += mainwindow.h \
           scanfolderthread.h \
           imageinfo.h \
           imagelistmodel.h \
           imageloader.h \
           imageloaderpool.h \
           imagewidget.h \
           slideshowlistmodel.h

SOURCES += main.cpp \
           mainwindow.cpp \
           scanfolderthread.cpp \
           imageinfo.cpp \
           imagelistmodel.cpp \
           imageloader.cpp \
           imageloaderpool.cpp \
           imagewidget.cpp \
           slideshowlistmodel.cpp

FORMS += mainwindow.ui


TRANSLATIONS = qsm_de.ts
CODECFORTR = ISO-8859-15
CODECFORSRC = UTF-8
