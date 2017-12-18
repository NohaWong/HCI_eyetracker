#include "bibliocellule.h"

biblioCellule::biblioCellule()
{

}

biblioCellule::biblioCellule(vector<Point*> ips, vector<Cellule*> adjacents){
    this->adjacents=adjacents;
    this->ips=ips;
}
