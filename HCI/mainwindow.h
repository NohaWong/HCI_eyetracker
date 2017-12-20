#ifndef BOOST_MAINWINDOW_H
#define BOOST_MAINWINDOW_H

#include <iostream>
#include <vector>
#include <QMessageBox>
#include <QtOpenGL/QGLWidget>
#include <QtGui/QtGui>
#include <QFileDialog>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>
#include <QListWidget>


#include "glwidget.h"

#include <boost/polygon/polygon.hpp>
#include <boost/polygon/voronoi.hpp>
using namespace boost::polygon;

#include "voronoi_visual_utils.h"



class MainWindow: public QWidget {
  Q_OBJECT

 public:
  MainWindow();

 private slots:
  void primary_edges_only();
  void internal_edges_only();

  void browse();

  void build();

  void print_scr();

 private:
QGridLayout* create_file_layout();

  void update_file_list();

  QDir file_dir_;
  QString file_name_;
  GLWidget* glWidget_;
  QListWidget* file_list_;
  QLabel* message_label_;
};







#endif // BOOST_MAINWINDOW_H
