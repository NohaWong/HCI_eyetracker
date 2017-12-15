#ifndef VORONOI_H
#define VORONOI_H
#include "Cellule.h"
#include "droite.h"
#include "bibliopoint.h"
#include "bibliocellule.h"
#include <iostream>

#define MAX 100000
class voronoi
{
public:
    voronoi();
    ~voronoi();
    void init(int width, int height,vector<Point> P);
    Cellule* whichCell(Point pt);
    biblioPoint intersectionDroitePolygone(vector<Point> lstPts,Droite droite);
    biblioCellule cutCell(Cellule *cell, Cellule *newcell);
    void addPoint(Point pt);
    vector<Cellule*> cellules;

private:
    int width;
    int height;

    int nbPoints;

    vector<Point> splice_Point(vector<Point> &v,int start, int howmuch,vector<Point> ar);
    vector<Cellule*> splice_Cellule(vector<Cellule*> &v,int start, int howmuch, const vector<Cellule*>& ar);
    bool DEBUG =0;

};

#endif // VORONOI_H
