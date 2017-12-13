#include "Cellule.h"


Cellule::Cellule(){
    this->nbSommets=0;
    this->id=-1;

}

Cellule::Cellule(int id)
{
    this->pt = Point(0.0,0.0);
    this->id=id;
    this->nbSommets=0;


}

float Cellule::distanceTo(Point pt){
    return pt.distanceTo(this->pt);
}

bool Cellule::equalCells(Cellule *cell){
    //cout << "EqualCells" << endl;
    //cout << "pt 1 ?" << pt.x << endl;
    //cout << "pt 2 ?" << cell->pt.x << endl;
    return pt.equal(cell->pt);
}

void Cellule::print(){
    this->printID();
    cout << "Point central = ";
    pt.print();

    cout << "Sommet :" << endl;
    int i;
    for(i=0;i<this->nbSommets;i++)
    {
        this->sommets[i].print();
    }

    cout << "ID cellule adjacente :" << endl;

    for(i=0;i<this->adjacents.size();i++)
    {
        this->adjacents[i]->printID();
    }
}

void Cellule::printID(){
    cout << "ID = " << id << endl;
}
