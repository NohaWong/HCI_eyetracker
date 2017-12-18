#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include "voronoi.h"
#include "point.h"
#include "qpainter.h"
#include "boost_point.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    vector<boost_Point> getAllPos();

    voronoi v;

    void paintEvent(QPaintEvent *event);
private:
    Ui::MainWindow *ui;
    boost_Point getCenterButton(QPushButton *button);

};

#endif // MAINWINDOW_H
