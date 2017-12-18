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
    mainwindow.cpp \
    voronoi.cpp \
    point.cpp \
    Cellule.cpp \
    droite.cpp \
    bibliopoint.cpp \
    bibliocellule.cpp \
    boost_voronoi.cpp \
    boost_point.cpp \
    boost_mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    voronoi.h \
    point.h \
    Cellule.h \
    droite.h \
    bibliopoint.h \
    bibliocellule.h \
    boost_voronoi.h \
    boost_point.h \
    voronoi_visual_utils.h \
    boost_mainwindow.h \
    glwidget.h

FORMS    += mainwindow.ui

LIBS += -lCGAL -lgmp -frounding-math -lm
