#include "boost_voronoi.h"

boost_voronoi::boost_voronoi(int w, int h)
{

    this->width = w;
    this->height=h;



}

void boost_voronoi::init(vector<Point> points)
{
    //Convertion
    for(int i=0;i<points.size();i++){
        point_data_.push_back(point_type(points[i].x,points[i].y));
    }





    construct_voronoi(point_data_.begin(), point_data_.end(),&vd_);


}



// TODO voir pour les lignes infinie

vector<Cellule> boost_voronoi::convert_into_Cellule(){
    vector<Cellule> cell_Vec;
    printf("DEBUT INIT\n");


    for (voronoi_diagram<double>::const_cell_iterator it = vd_.cells().begin();it != vd_.cells().end(); ++it) {
        printf("CELL\n");
        Cellule c;
        const voronoi_diagram<double>::cell_type &cell = *it;
        const voronoi_diagram<double>::edge_type *edge = cell.incident_edge();
        // This is convenient way to iterate edges around Voronoi cell.
        vector<point_type> samples;
        do {
            if (edge->is_infinite()){
                printf("INIFITY\n");
                clip_infinite_edge(*edge,&samples);
                Point *vertex0 = new Point(samples[0].x(), samples[0].y());
                Point *vertex1 = new Point(samples[0].x(), samples[0].y());
                c.sommets.push_back(vertex0);
                c.sommets.push_back(vertex1);
            }
            else{
                printf("NORMAL\n");
                Point *vertex0 = new Point(edge->vertex0()->x(), edge->vertex0()->y());
                Point *vertex1 = new Point(edge->vertex1()->x(), edge->vertex1()->y());
                c.sommets.push_back(vertex0);
                c.sommets.push_back(vertex1);

            }

            edge = edge->next();

        } while (edge != cell.incident_edge());
        cell_Vec.push_back(c);
    }

    for(int i=0;i<cell_Vec.size();i++){
        cell_Vec[i].print();
    }

    printf("FIN INIT\n");
    return cell_Vec;



}






void boost_voronoi::clip_infinite_edge(
    const edge_type& edge, std::vector<point_type>* clipped_edge) {
  const cell_type& cell1 = *edge.cell();
  const cell_type& cell2 = *edge.twin()->cell();
  point_type origin, direction;
  // Infinite edges could not be created by two segment sites.
  if (cell1.contains_point() && cell2.contains_point()) {
    point_type p1 = retrieve_point(cell1);
    point_type p2 = retrieve_point(cell2);
    origin.x((p1.x() + p2.x()) * 0.5);
    origin.y((p1.y() + p2.y()) * 0.5);
    direction.x(p1.y() - p2.y());
    direction.y(p2.x() - p1.x());
  } else {
    printf("ERROR in clip infinite edge");
      /* origin = cell1.contains_segment() ?
        retrieve_point(cell2) :
        retrieve_point(cell1);
    segment_type segment = cell1.contains_segment() ?
        retrieve_segment(cell1) :
        retrieve_segment(cell2);
    coordinate_type dx = high(segment).x() - low(segment).x();
    coordinate_type dy = high(segment).y() - low(segment).y();
    if ((low(segment) == origin) ^ cell1.contains_point()) {
      direction.x(dy);
      direction.y(-dx);
    } else {
      direction.x(-dy);
      direction.y(dx);
    }*/
  }
  cout << " rect : "<< xh(brect_) << ";"<<xl(brect_)<<  endl;
  coordinate_type side = xh(brect_) - xl(brect_);
  coordinate_type koef =
      side / (std::max)(fabs(direction.x()), fabs(direction.y()));
  if (edge.vertex0() == NULL) {
    clipped_edge->push_back(point_type(
        origin.x() - direction.x() * koef,
        origin.y() - direction.y() * koef));
  } else {
    clipped_edge->push_back(
        point_type(edge.vertex0()->x(), edge.vertex0()->y()));
  }
  if (edge.vertex1() == NULL) {
    clipped_edge->push_back(point_type(
        origin.x() + direction.x() * koef,
        origin.y() + direction.y() * koef));
  } else {
    clipped_edge->push_back(
        point_type(edge.vertex1()->x(), edge.vertex1()->y()));
  }
}




boost_voronoi::point_type boost_voronoi::retrieve_point(const cell_type& cell) {
  source_index_type index = cell.source_index();
  source_category_type category = cell.source_category();
  if (category == SOURCE_CATEGORY_SINGLE_POINT) {
    return point_data_[index];
  }
  printf("ERROR in retrieve point");/*
  index -= point_data_.size();
  if (category == SOURCE_CATEGORY_SEGMENT_START_POINT) {
    return low(segment_data_[index]);
  } else {
    return high(segment_data_[index]);
  }*/
  return point_data_[index];
}

