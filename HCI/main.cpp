/*#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "boost_voronoi.h"
#include "boost_voronoi.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    vector <boost_Point> Points = w.getAllPos();
    boost_voronoi v;
    v.init(Points);
    voronoi v;
    v.init(w.width(),w.height(),Points);






    w.v=v;

    w.show();

    a.exec();

    v.~voronoi();

    return 0;

}

*/

// Boost.Polygon library voronoi_visualizer.cpp file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#include <iostream>
#include <vector>
#include "boost_mainwindow.h"
#include <QMessageBox>
#include <QtOpenGL/QGLWidget>
#include <QtGui/QtGui>
#include <QApplication>

#include <boost/polygon/polygon.hpp>
#include <boost/polygon/voronoi.hpp>
using namespace boost::polygon;

#include "voronoi_visual_utils.h"



int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  boost_MainWindow window;
  window.show();
  return app.exec();
}

//#include "voronoi_visualizer.moc"
