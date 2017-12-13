#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "voronoi.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    vector <Point> Points = w.getAllPos();
    voronoi v;
    //v.init(w.width(),w.height(),Points);


    w.show();

    return a.exec();
}
