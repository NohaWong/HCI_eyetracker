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
    boost_voronoi.cpp \
    boost_mainwindow.cpp \
    glwidget.cpp

HEADERS  += \
    point.h \
    Cellule.h \
    boost_voronoi.h \
    voronoi_visual_utils.h \
    boost_mainwindow.h \
    glwidget.h

FORMS    +=

LIBS += -lCGAL -lgmp -frounding-math -lm
