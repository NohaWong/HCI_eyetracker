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

Point* Point::copy()
{
    return new Point(x,y);
}

float Point::distanceTo(Point *pt)
{
    float dx = x-pt->x;
    float dy = y-pt->y;
    return sqrt(pow(dx,2)+pow(dy,2));
}





bool Point::equal(Point *pt)
{
    return this->x== pt->x && this->y==pt->y;
}

void Point::print(){
    cout << "(" << x << "," << y << ")" << endl;
}


