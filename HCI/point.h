#ifndef POINT_H
#define POINT_H

#include <math.h>
#include <vector>
#include "droite.h"
#include <iostream>
using namespace std;

class Point
{
public:

    Point();
    bool equal(Point pt);
    Point(float x, float y);
    Point copy();
    float distanceTo(Point pt);
    float perProduct(Point p2);
    Droite mediatrice(Point pt);
    void print();


    float x;
    float y;



};

#endif // POINT_H
