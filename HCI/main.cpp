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
    v.init(w.width(),w.height(),Points);



    for(int i=0; i<v.cellules.size();i++)
    {
        v.cellules[i]->print();
    }


    w.v=v;

    w.show();

    a.exec();

    v.~voronoi();
    return 0;

}
