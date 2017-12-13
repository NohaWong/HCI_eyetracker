#include "voronoi.h"




/**
 * @brief Constructeur
 */
voronoi::voronoi()
{
    this->width=0;
    this->height=0;
    this->nbPoints=0;
    this->cellules = vector<Cellule*>();
}



/**
 * @brief Initialisation
 * @param width
 * @param height
 */
void voronoi::init(int width, int height, vector<Point> Points)
{
    this->width = width;
    this->height = height;
    // les 4 extremitees du canvas

    this->nbPoints=4;
    Cellule* hg = new Cellule(0);
    Cellule* hd = new Cellule(1);
    Cellule* bd = new Cellule(2);
    Cellule* bg = new Cellule(3);

    this->cellules.push_back(hg);
    this->cellules.push_back(hd);
    this->cellules.push_back(bd);
    this->cellules.push_back(bg);


    hg->pt = Point(-2*this->width, -2*this->height);
    hd->pt = Point(3*this->width, -2*this->height);
    bd->pt = Point(3*this->width, 3*this->height);
    bg->pt = Point(-2*this->width, 3*this->height);

    hg->sommets.push_back(Point(this->width/2, -MAX));
    hg->sommets.push_back(Point(this->width/2, this->height/2));
    hg->sommets.push_back(Point(-MAX, this->height/2));

    hd->sommets.push_back(Point(this->width/2, -MAX));
    hd->sommets.push_back(Point(MAX, this->height/2));
    hd->sommets.push_back(Point(this->width/2, this->height/2));

    bd->sommets.push_back(Point(this->width/2, this->height/2));
    bd->sommets.push_back(Point(MAX, this->height/2));
    bd->sommets.push_back(Point(this->width/2, MAX));

    bg->sommets.push_back(Point(-MAX, this->height/2));
    bg->sommets.push_back(Point(this->width/2, this->height/2));
    bg->sommets.push_back(Point(this->width/2, MAX));


    hg->nbSommets = 3;
    hd->nbSommets = 3;
    bd->nbSommets = 3;
    bg->nbSommets = 3;

    hg->adjacents.push_back(hd);
    hg->adjacents.push_back(bg);

    hd->adjacents.push_back(bd);
    hd->adjacents.push_back(hg);

    bd->adjacents.push_back(hd);
    bd->adjacents.push_back(bg);

    bg->adjacents.push_back(hg);
    bg->adjacents.push_back(bd);

    cout << "W = " << this->width << " H = " << this->height << endl;

    /*hg->print();
    hd->print();
    bd->print();
    bg->print();*/
    Points[0].print();
    this->addPoint(Points[0]);
    /*
    int i;
    for(i=0;i<Points.size();i++){
        this->addPoint(Points[i]);
    }*/


}

/**
 * Méthode whichCell
 * renvoie la cellule du diagramme de
 * Voronoi contenant le point pt.
 */
Cellule* voronoi::whichCell(Point pt){
    float dmin = MAX;
    float tmp;
    Cellule* cellmin;
    int i;
    for(i=0;i<this->nbPoints;i++){
        tmp=this->cellules[i]->distanceTo(pt);
        if(tmp<dmin){
            dmin=tmp;
            cellmin = this->cellules[i];
        }
    }
    return cellmin;
}

/**
 * Fonction intersectionDroitePolygone
 * renvoie les points d'intersection entre la droite
 * et le polygone represente par l'ensemble de ses
 * sommets.
 * renvoie aussi les numeros i des points tel que
 * les points d'intersection se trouvent entre i et i+1
 */


biblioPoint voronoi::intersectionDroitePolygone(vector<Point> lstPts,Droite droite){
    vector<Point> ptsIntersect;
    vector<int> numPts;
    Point lastPt = lstPts[0];
    Point currentPt,segment;
    int nbPts = lstPts.size();
    int i;
    float num,denom,t,ipx,ipy;

    for(i=0;i<nbPts;i++){
        currentPt = lstPts[(i+1)%nbPts];
        // le segment de droite que l'on considère est de
        // la forme (t*(cx - lx) + lx, t*(cy - ly) + ly)
        // avec t dans [0, 1]
        segment = Point(currentPt.x - lastPt.x, currentPt.y-lastPt.y);
        // par identification entre les deux equations de droite
        // on détermine le moment d'intersection t qui doit Ãªtre
        // dans [0, 1]
        num = droite.c + droite.a*lastPt.x + droite.b*lastPt.y;
        denom = droite.a*segment.x + droite.b*segment.y;
        t = -num/denom;
        // si le point d'intersection est bien sur le segment
        if(t>=0&& t<=1){
            // on calcul le point d'intersection
            ipx = t*segment.x + lastPt.x;
            ipy = t*segment.y + lastPt.y;
            ptsIntersect.push_back(Point(ipx,ipy));
            numPts.push_back(i);

        }
        lastPt = currentPt;
    }

    return biblioPoint(ptsIntersect,numPts);
}

/**
 * Fonction auxiliaire pour la fabrication
 * des nouvelles cellules a l'ajout de points
 */

biblioCellule voronoi::cutCell(Cellule *cell, Cellule *newcell){
    //La médiatrice
    Droite med = cell->pt.mediatrice(newcell->pt);
    //Détermination des (2!) points d'intersection
    biblioPoint itscs= intersectionDroitePolygone(cell->sommets,med);
    vector<Point> ips = itscs.ips;
    vector<int> nums = itscs.nums;



    // Attention ça peut etre NULLLLLLLLLLLLL
    Cellule *firstAdj = cell->adjacents[nums[0]];
    Cellule *lastAdj = cell->adjacents[nums[1]];

    firstAdj->print();
    lastAdj->print();

    //On détermine les nouveaux sommets de la cellule


    vector<Point> tmp_ips;
    tmp_ips.push_back(ips[0]);
    tmp_ips.push_back(ips[1]);
    vector<Cellule*> tmp_adj;
    tmp_adj.push_back(firstAdj);
    tmp_adj.push_back(lastAdj);

    vector<Point> tmp_sommets = splice_Point(cell->sommets,nums[0]+1,nums[1]-nums[0],tmp_ips);//cell.sommets;
    vector<Cellule*> tmp_adjacents = splice_Cellule(cell->adjacents,nums[0]+1,nums[1]-nums[0],tmp_adj);

    // on verifie de quel cote de la cellule coupe
    // en deux on garde pour elle meme
    float d1 = newcell->distanceTo(cell->sommets[0]);
    float d2 = cell->distanceTo(cell->sommets[0]);

    if(d2 > d1){
          cell->sommets = tmp_sommets;
          cell->sommets.insert(cell->sommets.begin(),ips[0]);
          cell->sommets.push_back(ips[1]);
          cell->adjacents = tmp_adjacents;
          cell->adjacents.insert(cell->adjacents.begin(),firstAdj);
          cell->adjacents.push_back(newcell);
    }
    cell->nbSommets = cell->sommets.size();


    return biblioCellule(ips,tmp_adj);


}




vector<Point> voronoi::splice_Point(vector<Point> v,int start, int howmuch, const vector<Point>& ar){
    vector<Point> result(v.begin()+start,v.begin()+start+howmuch);
    v.erase(v.begin()+start,v.begin()+start+howmuch);
    v.insert(v.begin()+start,ar.begin(),ar.begin());
    return result;
}


vector<Cellule*> voronoi::splice_Cellule(vector<Cellule*> &v,int start, int howmuch, const vector<Cellule*>& ar){
    vector<Cellule*> result;
    if(v.size() > start)
    {
        result = vector<Cellule*>(v.begin()+start,v.begin()+start+howmuch);
        v.erase(v.begin()+start,v.begin()+start+howmuch);
    }
  //  cout << "size = " << v.size() << " start = " << start << "howmuch = " << howmuch << endl;


  //  v.insert(v.begin()+start,ar.begin(),ar.end());
    cout << "FIN" << endl;
    return result;
}



void voronoi::addPoint(Point pt){

    // On détermine dans quel cellule déjà creer , le point se trouve
    Cellule* cellmin = this->whichCell(pt);
    if(pt.x == cellmin->pt.x && pt.y == cellmin->pt.y) return;


    // On creer une nouvelle cellule
    Cellule* cell = new Cellule(this->nbPoints);
    this->cellules[this->nbPoints]=cell;


    cell->pt = pt;

    // On coupe en deux la cellule obtenu
    // selon la médiatrice entre le point
    // courante et le point de la cellule
    biblioCellule tmp = cutCell(cellmin,cell);


    cout << "cellmin" << endl;
    cellmin->print();
    cout << "cell" << endl;
    cell->print();
    vector<Point> ips = tmp.ips;
    Cellule* first = tmp.adjacents[0];
    Cellule* last = tmp.adjacents[1];

    // On determine la cellule pour le nouveau point
    // TODO Verifier pour ips , si il y a besoin de faire un ips[0].copy
    cell->sommets.push_back(ips[0]);
    cell->adjacents.push_back(first);
    Cellule* prec = cellmin;
    Cellule* suivant = first;

    while(!suivant->equalCells(last)){
        tmp = cutCell(suivant,cell);
       // vector<Cellule *> adj = tmp.adjacents;
        Cellule* prec_tmp = suivant;
        int num = prec->equalCells(tmp.adjacents[0]) ? 1 : 0;
        suivant = tmp.adjacents[num];
        prec = prec_tmp;

        cell->sommets.push_back(tmp.ips[num].copy());
        cell->adjacents.push_back(suivant);
    }

    cutCell(suivant,cell);
    cell->sommets.push_back(ips[1]);
    cell->adjacents.push_back(cellmin);

    cell->nbSommets = cell->sommets.size();

    this->nbPoints++;
}


















