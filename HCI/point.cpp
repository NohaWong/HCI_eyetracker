#include "point.h"


Point::Point()
{
    x=0.0;
    y=0.0;
}


Point::Point(float x, float y)
{
    this->x=x;
    this->y=y;
}

Point Point::copy()
{
    return Point(x,y);
}

float Point::distanceTo(Point pt)
{
    float dx = x-pt.x;
    float dy = y-pt.y;
    return sqrt(pow(dx,2)+pow(dy,2));
}

float Point::perProduct(Point p2)
{
    return x*y - p2.x*p2.y;
}

vector<float> Point::mediatrice(Point pt)
{
    std::vector<float> droite;
    Point milieu = Point((x+pt.x)/2,(y+pt.y)/2);

    droite.push_back(pt.x-x);
    droite.push_back(pt.y-y);
    droite.push_back(-(droite[1]*milieu.y + droite[0]*milieu.x));

    return droite;
}

bool Point::equal(Point pt)
{
    return this->x== pt.x && this->y==pt.y;
}
