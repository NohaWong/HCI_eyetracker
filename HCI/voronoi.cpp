#include "voronoi.h"




/**
 * @brief Constructeur
 */
voronoi::voronoi()
{
    this->width=0;
    this->height=0;
    this->cellules = vector<Cellule*>();
}


voronoi::~voronoi(){
    int i;
    for(i=0;i<cellules.size();i++)
        delete cellules[i];

}


/**
    Initilisation du voronoi. On creer 4 cellule triangulaire qui englobe la fenetre

*/
void voronoi::init(int width, int height, vector<Point> Points)
{
    this->width = width;
    this->height = height;
    // les 4 extremitees du canvas

    Cellule* hg = new Cellule(0);
    Cellule* hd = new Cellule(1);
    Cellule* bd = new Cellule(2);
    Cellule* bg = new Cellule(3);

    this->cellules.push_back(hg);
    this->cellules.push_back(hd);
    this->cellules.push_back(bd);
    this->cellules.push_back(bg);


    hg->pt = new Point(-2*this->width, -2*this->height);
    hd->pt = new Point(3*this->width, -2*this->height);
    bd->pt = new Point(3*this->width, 3*this->height);
    bg->pt = new Point(-2*this->width, 3*this->height);


   // NEW TEST
    hg->sommets.push_back(new Point(this->width/2, this->height/2));
    hg->sommets.push_back(new Point(-MAX, this->height/2));
    hg->sommets.push_back(new Point(this->width/2, -MAX));


    hd->sommets.push_back(new Point(this->width/2, this->height/2));
    hd->sommets.push_back(new Point(this->width/2, -MAX));
    hd->sommets.push_back(new Point(MAX, this->height/2));

    bd->sommets.push_back(new Point(this->width/2, this->height/2));
    bd->sommets.push_back(new Point(MAX, this->height/2));
    bd->sommets.push_back(new Point(this->width/2, MAX));


    bg->sommets.push_back(new Point(this->width/2, this->height/2));
    bg->sommets.push_back(new Point(this->width/2, MAX));
    bg->sommets.push_back(new Point(-MAX, this->height/2));





    hg->adjacents.push_back(bg);
    hg->adjacents.push_back(new Cellule());
    hg->adjacents.push_back(hd);


    hd->adjacents.push_back(hg);
    hd->adjacents.push_back(new Cellule());
    hd->adjacents.push_back(bd);


    bd->adjacents.push_back(hd);
    bd->adjacents.push_back(new Cellule());
    bd->adjacents.push_back(bg);


    bg->adjacents.push_back(bd);
    bg->adjacents.push_back(new Cellule());
    bg->adjacents.push_back(hg);



/*
   //OLD
    hg->sommets.push_back(new Point(this->width/2, -MAX));
    hg->sommets.push_back(new Point(this->width/2, this->height/2));
    hg->sommets.push_back(new Point(-MAX, this->height/2));




    hd->sommets.push_back(new Point(this->width/2, -MAX));
    hd->sommets.push_back(new Point(MAX, this->height/2));
    hd->sommets.push_back(new Point(this->width/2, this->height/2));

    bd->sommets.push_back(new Point(this->width/2, this->height/2));
    bd->sommets.push_back(new Point(MAX, this->height/2));
    bd->sommets.push_back(new Point(this->width/2, MAX));

    bg->sommets.push_back(new Point(-MAX, this->height/2));
    bg->sommets.push_back(new Point(this->width/2, this->height/2));
    bg->sommets.push_back(new Point(this->width/2, MAX));





    // On ajoute ne plus des 2 voisins, une cellule vide qui correspont à la 3eme face de chaque triangle. Cette cellule n'est jamais utilisé mais sert pour le décompte des cellules adjacente
    hg->adjacents.push_back(hd);
    hg->adjacents.push_back(bg);
    hg->adjacents.push_back(new Cellule());

    hd->adjacents.push_back(new Cellule());
    hd->adjacents.push_back(bd);
    hd->adjacents.push_back(hg);


    bd->adjacents.push_back(hd);
    bd->adjacents.push_back(new Cellule());
    bd->adjacents.push_back(bg);

    bg->adjacents.push_back(hg);
    bg->adjacents.push_back(bd);
    bg->adjacents.push_back(new Cellule());
*/

   // this->cellules[1]->print();

    this->addPoint(&Points[0]);


    this->addPoint(&Points[1]);
    for(int i=0;i<this->cellules.size();i++)
        this->cellules[i]->print();

    DEBUG=1;
    //this->addPoint(&Points[2]);
    int i;
    for(i=0;i<Points.size();i++){
    //    this->addPoint(Points[i]);
    }


}

/**
 * Méthode whichCell
 * renvoie la cellule du diagramme de
 * Voronoi contenant le point pt.
 */
Cellule* voronoi::whichCell(Point *pt){
    float dmin = MAX;
    float tmp;
    Cellule* cellmin;
    int i;
    for(i=0;i<this->cellules.size();i++){
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


biblioPoint voronoi::intersectionDroitePolygone(vector<Point*> lstPts,Droite droite){
    vector<Point*> ptsIntersect;
    vector<int> numPts;
    Point* lastPt = lstPts[0];
    Point* currentPt;
    Point* segment;
    int nbPts = lstPts.size();
    int i;
    float num,denom,t,ipx,ipy;

  /*  if(DEBUG){
        droite.print();
        cout << "nbPts : " << nbPts << endl;
    }*/
    for(i=0;i<nbPts;i++){


        currentPt = lstPts[(i+1)%nbPts];
      /*  if(DEBUG)
        {
            lastPt.print();
            currentPt.print();
        }*/
        // le segment de droite que l'on considère est de
        // la forme (t*(cx - lx) + lx, t*(cy - ly) + ly)
        // avec t dans [0, 1]
        segment = new Point(currentPt->x - lastPt->x, currentPt->y-lastPt->y);
        // par identification entre les deux equations de droite
        // on détermine le moment d'intersection t qui doit Ãªtre
        // dans [0, 1]
        num = droite.c + droite.a*lastPt->x + droite.b*lastPt->y;
        denom = droite.a*segment->x + droite.b*segment->y;



        t = -num/denom;

        // si le point d'intersection est bien sur le segment
        if(t>=0&& t<=1){
            // on calcul le point d'intersection
            ipx = t*segment->x + lastPt->x;
            ipy = t*segment->y + lastPt->y;
            ptsIntersect.push_back(new Point(ipx,ipy));
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


    if(DEBUG)
        cout << "DEBUT CUTCELL" << endl;
    Droite med = cell->pt->mediatrice(newcell->pt);

    //Détermination des (2!) points d'intersection
    biblioPoint itscs= intersectionDroitePolygone(cell->sommets,med);
    vector<Point*> ips = itscs.ips;
    vector<int> nums = itscs.nums;
    if(nums.size() != 2)
    {

        cout << "ERROR dans intersectionDroitePolygone, point d'intersection non trouvé" << endl;
        cout << "nb intersection trouvé :" << nums.size() << endl;

    }

    if(DEBUG){
        //cell->print();
        cout << "num : " << nums[0] << " " <<nums[1] << endl;
    }
        // Attention ça peut etre NULLLLLLLLLLLLL
    Cellule *firstAdj = cell->adjacents[nums[0]];
    Cellule *lastAdj = cell->adjacents[nums[1]];


    //On détermine les nouveaux sommets de la cellule

    vector<Point*> tmp_ips;
    tmp_ips.push_back(ips[0]);
    tmp_ips.push_back(ips[1]);
    vector<Cellule *> vec_lastAdj;
    vec_lastAdj.push_back(lastAdj);



    vector<Point*> tmp_sommets = splice_Point(cell->sommets,nums[0]+1,nums[1]-nums[0],tmp_ips);
    if(DEBUG)
        cout << "FLAG1" << endl;
    vector<Cellule*> tmp_adjacents = splice_Cellule(cell->adjacents,nums[0]+1,nums[1]-nums[0],vec_lastAdj);


    // on verifie de quel cote de la cellule coupe
    // en deux on garde pour elle meme
    float d1 = newcell->distanceTo(cell->sommets[0]);
    float d2 = cell->distanceTo(cell->sommets[0]);

    cell->printID();
    cout << "d1: " << d1 << " d2: " << d2 << endl;

    if(d2 > d1){
          cout << "On insert dans cellule :" ;
          cell->printID();
          cell->sommets = tmp_sommets;
          cell->sommets.insert(cell->sommets.begin(),ips[0]);
          cell->sommets.push_back(ips[1]);
          cell->adjacents = tmp_adjacents;
          cell->adjacents.insert(cell->adjacents.begin(),firstAdj);
          cell->adjacents.push_back(newcell);
    }

    if(DEBUG)
        cout << "FIN CUTCELL" << endl;


    vector<Cellule*> tmp_adj;
    tmp_adj.push_back(firstAdj);
    tmp_adj.push_back(lastAdj);

    return biblioCellule(ips,tmp_adj);


}




vector<Point*> voronoi::splice_Point(vector<Point*> &v,int start, int howmuch,vector<Point*> ar){
    vector<Point*> result(v.begin()+start,v.begin()+start+howmuch);
    v.erase(v.begin()+start,v.begin()+start+howmuch);
    v.insert(v.begin()+start,ar.begin(),ar.end());
    return result;
}


vector<Cellule*> voronoi::splice_Cellule(vector<Cellule*> &v,int start, int howmuch, const vector<Cellule*>& ar){
    vector<Cellule*> result;
    result = vector<Cellule*>(v.begin()+start,v.begin()+start+howmuch);
    v.erase(v.begin()+start,v.begin()+start+howmuch);
    v.insert(v.begin()+start,ar.begin(),ar.end());
    return result;
}



void voronoi::addPoint(Point *pt){

    // On détermine dans quel cellule déjà creer , le point se trouve
    if(DEBUG)
        cout << "DEBUT ADD POINT" << endl;
    Cellule* cellmin = this->whichCell(pt);
    if(pt->x == cellmin->pt->x && pt->y == cellmin->pt->y) return;


    // On creer une nouvelle cellule
    Cellule* cell = new Cellule(this->cellules.size());
    this->cellules.push_back(cell);
    cell->pt = pt;

    // On coupe en deux la cellule obtenu
    // selon la médiatrice entre le point
    // courante et le point de la cellule
    biblioCellule tmp = cutCell(cellmin,cell);

    vector<Point*> ips = tmp.ips;
    Cellule* first = tmp.adjacents[0];
    Cellule* last = tmp.adjacents[1];


    // On determine la cellule pour le nouveau point
    // TODO Verifier pour ips , si il y a besoin de faire un ips[0].copy
    cell->sommets.push_back(ips[0]->copy());
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

        cell->sommets.push_back(tmp.ips[num]->copy());
        cell->adjacents.push_back(suivant);
    }

    cutCell(suivant,cell);
    cell->sommets.push_back(ips[1]->copy());
    cell->adjacents.push_back(cellmin);

    if(DEBUG)
        cout << "FIN ADD POINT" << endl;
}


















