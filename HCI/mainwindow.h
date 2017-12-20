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
#include <QGroupBox>
#include <QRadioButton>

#include "glwidget.h"
#include "point.h"

#include <boost/polygon/polygon.hpp>
#include <boost/polygon/voronoi.hpp>
using namespace boost::polygon;

#include "voronoi_visual_utils.h"



class MainWindow: public QWidget {
  Q_OBJECT

 public:
  MainWindow();

  void write_data();


private slots:



  void Exp_1_Clicked();
  void Exp_2_Clicked();
  void Exp_3_Clicked();
    void next_file();

  void browse();

  void build();

  void print_scr();



 private:
QGridLayout* create_file_layout();

  void update_file_list();

  void init_file();
  QDir file_dir_;
  QString file_name_;
  GLWidget* glWidget_;
  QListWidget* file_list_;
  QLabel* message_label_;

  QStringList file_name_Exp_;
  int index_exp;



};







#endif // BOOST_MAINWINDOW_H
