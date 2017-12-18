#include "boost_voronoi.h"

boost_voronoi::boost_voronoi()
{


}




void boost_voronoi::init(vector<boost_Point> points){
    construct_voronoi(points.begin(), points.end(),
                      //segments.begin(), segments.end(),
                      &vd);


    // Traversing Voronoi Graph.
    {
      printf("Traversing Voronoi graph.\n");
      printf("Number of visited primary edges using edge iterator: %d\n",
          iterate_primary_edges1());
      printf("Number of visited primary edges using cell iterator: %d\n",
          iterate_primary_edges2());
      printf("Number of visited primary edges using vertex iterator: %d\n",
          iterate_primary_edges3());
      printf("\n");
    }

    // Using color member of the Voronoi primitives to store the average number
    // of edges around each cell (including secondary edges).
    {
      printf("Number of edges (including secondary) around the Voronoi cells:\n");
      for (voronoi_diagram<double>::const_edge_iterator it = vd.edges().begin();
           it != vd.edges().end(); ++it) {
        std::size_t cnt = it->cell()->color();
        it->cell()->color(cnt + 1);
      }
      for (voronoi_diagram<double>::const_cell_iterator it = vd.cells().begin();
           it != vd.cells().end(); ++it) {
        printf("%lu ", it->color());
      }
      printf("\n");
      printf("\n");
    }
    // Linking Voronoi cells with input geometries.
    {
      unsigned int cell_index = 0;
      for (voronoi_diagram<double>::const_cell_iterator it = vd.cells().begin();
           it != vd.cells().end(); ++it) {
        if (it->contains_point()) {
          std::size_t index = it->source_index();
          boost_Point p = points[index];
          printf("Cell #%ud contains a point: (%d, %d).\n",
                 cell_index, x(p), y(p));
        } else {
          printf("ERROR\n");
        }
        ++cell_index;
      }
    }



    for (voronoi_diagram<double>::const_cell_iterator it = vd.cells().begin();
        it != vd.cells().end(); ++it)
    {

        const cell_type& cell = *it;
        const edge_type* edge = cell.incident_edge();

        do
        {

            if (edge->is_primary())
            {
                // Easy finite edge case
                if (edge->is_finite())
                {
                    // Without this check each edge would be drawn twice
                    // as they are really half-edges
                    if (edge->cell()->source_index() <
                        edge->twin()->cell()->source_index())
                    {
                       cout << edge->vertex0()->x() << edge->vertex0()->y() << edge->vertex1()->x() << edge->vertex1()->y() << endl;
                    }
                }
                else{
                    cout << "I GOT INFINIT EDGE" << endl;
                }
            }
            edge = edge->next();
        } while (edge != cell.incident_edge());
    }

}






// Traversing Voronoi edges using edge iterator.
int boost_voronoi::iterate_primary_edges1() {
  int result = 0;
  for (voronoi_diagram<double>::const_edge_iterator it = vd.edges().begin();
       it != vd.edges().end(); ++it) {
    if (it->is_primary())
      ++result;
  }
  return result;
}




// Traversing Voronoi edges using cell iterator.
int boost_voronoi::iterate_primary_edges2() {
  int result = 0;
  for (voronoi_diagram<double>::const_cell_iterator it = vd.cells().begin();
       it != vd.cells().end(); ++it) {
    const voronoi_diagram<double>::cell_type& cell = *it;

    const voronoi_diagram<double>::edge_type* edge = cell.incident_edge();

    // This is convenient way to iterate edges around Voronoi cell.
    do {

      if (edge->is_primary())
        ++result;
      edge = edge->next();
    } while (edge != cell.incident_edge());
  }
  return result;
}


int boost_voronoi::iterate_primary_edges3() {
  int result = 0;
  for (voronoi_diagram<double>::const_vertex_iterator it =
       vd.vertices().begin(); it != vd.vertices().end(); ++it) {
    const voronoi_diagram<double>::vertex_type& vertex = *it;
    const voronoi_diagram<double>::edge_type* edge = vertex.incident_edge();
    // This is convenient way to iterate edges around Voronoi vertex.
    do {
      if (edge->is_primary())
        ++result;
      edge = edge->rot_next();
    } while (edge != vertex.incident_edge());
  }
  return result;
}

