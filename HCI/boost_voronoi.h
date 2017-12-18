#ifndef BOOST_VORONOI_H
#define BOOST_VORONOI_H


#include <cstdio>
#include <vector>
#include "boost_point.h"
#include <iostream>
#include <boost/polygon/voronoi.hpp>
using boost::polygon::voronoi_builder;
using boost::polygon::voronoi_diagram;
using boost::polygon::x;
using boost::polygon::y;
using boost::polygon::low;
using boost::polygon::high;


typedef voronoi_diagram<double>::cell_type cell_type;
typedef voronoi_diagram<double>::edge_type edge_type;
typedef voronoi_diagram<double>::vertex_type vertex_type;
using namespace std;

class boost_voronoi
{
public:

    voronoi_diagram<double> vd;


    boost_voronoi();
    void init(vector<boost_Point> points);




    // Traversing Voronoi edges using edge iterator.
    int iterate_primary_edges1();
    // Traversing Voronoi edges using cell iterator.
    int iterate_primary_edges2();
    // Traversing Voronoi edges using vertex iterator.
    // As opposite to the above two functions this one will not iterate through
    // edges without finite endpoints and will iterate only once through edges
    // with single finite endpoint.
    int iterate_primary_edges3();










};




namespace boost {
namespace polygon {

template <>
struct geometry_concept<boost_Point> {
  typedef point_concept type;
};

template <>
struct point_traits<boost_Point> {
  typedef int coordinate_type;

  static inline coordinate_type get(
      const boost_Point& point, orientation_2d orient) {
    return (orient == HORIZONTAL) ? point.x : point.y;
  }
};

}  // polygon
}  // boost





#endif // BOOST_VORONOI_H
