#ifndef VORONOI_H
#define VORONOI_H


#include <iostream>
#include <fstream>
#include <cassert>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Voronoi_diagram_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_traits_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_policies_2.h>

class voronoi
{
public:
    voronoi();
};

#endif // VORONOI_H
