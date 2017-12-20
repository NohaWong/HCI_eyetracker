#ifndef GLWidget_H
#define GLWidget_H

#include <QtOpenGL/QGLWidget>
#include <QtGui/QtGui>
#include <QMainWindow>
#include <QGridLayout>
#include <QListWidget>
#include <QMessageBox>
#include <boost/polygon/polygon.hpp>
#include <boost/polygon/voronoi.hpp>
#include <QGLWidget>
#include "point.h"
#include <iostream>
#include <cstdio>
using namespace std;
using namespace boost::polygon;

#include "voronoi_visual_utils.h"
class GLWidget : public QGLWidget {
  Q_OBJECT

 public:
  explicit GLWidget(QMainWindow* parent = NULL) :
      QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
      primary_edges_only_(false),
      internal_edges_only_(false), index_of_voronoi_active_(false) {
    startTimer(40);
  }

  QSize sizeHint() const;
    bool end_exp_;
  void build(const QString& file_path);
  void draw_end_experience();
  void color_a_voronoi_cell(Point p);

 protected:
  void initializeGL();

  void paintGL();

  void resizeGL(int width, int height);

  void timerEvent(QTimerEvent* e);

 private:
  typedef double coordinate_type;
  typedef point_data<coordinate_type> point_type;
  typedef segment_data<coordinate_type> segment_type;
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
  static const std::size_t EXTERNAL_COLOR = 1;


  typedef enum {CIRCLE,CROSS,SQUARE,TRIANGLE}FORM;
  typedef enum {RED,BLUE,YELLOW,GREEN}COLOR;



  void clear();

  void read_data(const QString& file_path);

  void update_brect(const point_type& point);

  void construct_brect();

  void color_exterior(const VD::edge_type* edge);

  void update_view_port();

  void draw_points();

  //void draw_segments();

  void draw_vertices();
  void draw_edges();
  void draw_circle(point_type center,int color);
  void draw_cross(point_type center,int color);
  void draw_square(point_type center,int color);
  void draw_triangle(point_type center,int color);
  void draw_button(point_type center);
  void draw_voronoi_cell();

  void start_color(int color);

  void clip_infinite_edge(const edge_type& edge, std::vector<point_type>* clipped_edge);

    // Renvoi vrai si p1 est plus proche de l'origine que p2
  bool isCloser(point_type origin, point_type p1, point_type p2);





  /*void sample_curved_edge(
     const edge_type& edge,
      std::vector<point_type>* sampled_edge);
*/
point_type retrieve_point(const cell_type& cell);

  //segment_type retrieve_segment(const cell_type& cell);

  point_type shift_;
  vector<int> point_form_;
  vector<int> point_color_;

  double size_form_;

  std::vector<point_type> point_data_;
  std::vector<segment_type> segment_data_;
  rect_type brect_;
  VB vb_;
  VD vd_;
  bool brect_initialized_;
  bool primary_edges_only_;
  bool internal_edges_only_;
  bool do_draw_voronoi_cell_;
  int index_of_voronoi_active_;



};

#endif // GLWidget_H
