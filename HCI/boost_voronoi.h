#ifndef BOOST_VORONOI_H
#define BOOST_VORONOI_H


#include <cstdio>
#include <vector>
#include <iostream>
#include <boost/polygon/voronoi.hpp>
#include <Cellule.h>
#include <point.h>




using namespace boost::polygon;
using namespace std;

class boost_voronoi
{
public:
    typedef double coordinate_type;
    typedef point_data<coordinate_type> point_type;
    typedef rectangle_data<coordinate_type> rect_type;
    typedef voronoi_builder<int> VB;
    typedef voronoi_diagram<coordinate_type> VD;
    typedef VD::cell_type cell_type;
    typedef VD::cell_type::source_index_type source_index_type;
    typedef VD::cell_type::source_category_type source_category_type;
    typedef VD::edge_type edge_type;
    typedef VD::cell_container_type cell_container_type;
    typedef VD::cell_container_type vertex_container_type;
    typedef VD::edge_container_type edge_container_type;
    typedef VD::const_cell_iterator const_cell_iterator;
    typedef VD::const_vertex_iterator const_vertex_iterator;
    typedef VD::const_edge_iterator const_edge_iterator;

    point_type shift_;
    std::vector<point_type> point_data_;
    rect_type brect_;
    VD vd_;
    bool brect_initialized_;
    bool primary_edges_only_;
    bool internal_edges_only_;



    int width;
    int height;



    boost_voronoi();
    boost_voronoi(int w, int h);
    void init(vector<Point> points);


    vector<Cellule> convert_into_Cellule();
    void clip_infinite_edge(const edge_type& edge, std::vector<point_type>* clipped_edge);
    point_type retrieve_point(const cell_type& cell);









};







#endif // BOOST_VORONOI_H
