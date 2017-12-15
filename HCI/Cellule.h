#ifndef CELLULE_H
#define CELLULE_H
#include <vector>
#include "point.h"
#include <iostream>
#include <QPolygon>
#include <QVector>
using namespace std;

class Cellule
{
public:
    Cellule();
    Cellule(int id);
    float distanceTo(Point pt);
    bool  equalCells(Cellule *cell);
    Point pt;
    int id;
    vector<Point> sommets;
    int nbSommets;
    vector<Cellule*> adjacents;
    void print();
    void printID();
    QVector<QPoint> point_to_qpoint();

private:



};

#endif // CELLULE_H
