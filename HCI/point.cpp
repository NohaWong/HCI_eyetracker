#include "point.h"

Point::Point(float x, float y)
{
    this->x=x;
    this->y=y,
}

Point Point::copy()
{
    return new Point(this->x,this->y);
}

float Point::distance_to(Point pt)
{
    float dx = this->x-pt.x;
    float dy = this->y-pt.y;
    return sqrt(pow(dx,2)+pow(dy,2));
}

float Point::per_product(Point p2)
{
    return this.x*this.y - p2.x*p2.y;
}

vector<float> Point::mediatrice(Point pt)
{
    std::vector<float> droite;
    float milieu = new Point((this->x+pt.x)/2,(this->y+pt.y)/2);

    droite.push_back(pt.x-this->x);
    droite.push_back(pt.y-this->y);
    droite.push_back(-(droite.at(1)*milieu.y + droite.at(0)*milieu.x));

    return droite;
}
