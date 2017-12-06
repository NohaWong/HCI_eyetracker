#ifndef POINT_H
#define POINT_H

#include <math.h>
#include <vector>

using namespace std;

class Point
{
public:
    Point(float x, float y);
    Point copy();
    float distanceTo(Point pt);
    float perProduct(Point p2);
    vector<float> mediatrice(Point pt);
    float x;
    float y;

};

#endif // POINT_H
