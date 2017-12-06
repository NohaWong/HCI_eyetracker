#ifndef POINT_H
#define POINT_H

#include <math.h>
#include <vector>

class Point
{
public:
    Point(float x, float y);
    Point Point::copy();
    float Point::distance_to(Point pt);
    float Point::per_product(Point p2);
    vector<float> Point::mediatrice(Point pt);
private:
    float x;
    float y;

};

#endif // POINT_H
