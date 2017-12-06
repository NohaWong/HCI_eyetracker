#-------------------------------------------------
#
# Project created by QtCreator 2017-11-24T09:44:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HCI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    voronoi.cpp \
    point.cpp

HEADERS  += mainwindow.h \
    voronoi.h \
    point.h

FORMS    += mainwindow.ui

LIBS += -lCGAL -lgmp -frounding-math -lm
