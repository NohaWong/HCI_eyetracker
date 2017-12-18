#include "Cellule.h"


Cellule::Cellule(){
    this->id=-1;

}

Cellule::Cellule(int id)
{
    this->pt = new Point(0.0,0.0);
    this->id=id;
}


float Cellule::distanceTo(Point *pt){
    return pt->distanceTo(this->pt);
}

bool Cellule::equalCells(Cellule *cell){
    //cout << "EqualCells" << endl;
    //cout << "pt 1 ?" << pt.x << endl;
    //cout << "pt 2 ?" << cell->pt.x << endl;
    return pt->equal(cell->pt);
}

void Cellule::print(){
    this->printID();
    cout << "Point central = ";
    pt->print();

    cout << "Sommet :" << endl;
    int i;
    for(i=0;i<sommets.size();i++)
    {
        this->sommets[i]->print();
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

QVector<QPoint> Cellule::point_to_qpoint(){
    QVector<QPoint> res;
    QPoint p;
    int x_cord,y_cord;
    for(int i=4;i<this->sommets.size();i++){
        x_cord=this->sommets[i]->x;
        y_cord=this->sommets[i]->y;
        p = QPoint(x_cord,y_cord);
        res.push_back(p);
    }
    return res;

}
