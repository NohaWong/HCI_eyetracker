#ifndef BIBLIOCELLULE_H
#define BIBLIOCELLULE_H
#include <vector>
#include "point.h"
#include "Cellule.h"


using namespace std;

class biblioCellule
{
public:
    biblioCellule();
    biblioCellule(vector<Point*> ips,vector<Cellule*> adjacents);
    vector<Point*> ips;
    vector<Cellule*> adjacents;
};

#endif // BIBLIOCELLULE_H
