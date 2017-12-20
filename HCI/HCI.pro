#-------------------------------------------------
#
# Project created by QtCreator 2017-11-24T09:44:52
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HCI
TEMPLATE = app


SOURCES +=\
    main.cpp \
    point.cpp \
    Cellule.cpp \
    glwidget.cpp \
    mainwindow.cpp

HEADERS  += \
    point.h \
    Cellule.h \
    voronoi_visual_utils.h \
    glwidget.h \
    mainwindow.h

FORMS    +=

LIBS +=  -frounding-math -lm
