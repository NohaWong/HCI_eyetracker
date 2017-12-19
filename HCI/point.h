#ifndef POINT_H
#define POINT_H

#include <math.h>
#include <vector>
#include <iostream>
using namespace std;

class Point
{
public:

    Point();
    bool equal(Point *pt);
    Point(float x, float y);
    Point* copy();
    float distanceTo(Point *pt);
    void print();

    double x;
    double y;



};

#endif // POINT_H
