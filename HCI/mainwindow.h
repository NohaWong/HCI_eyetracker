#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include "voronoi.h"
#include "point.h"
#include "qpainter.h"


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

    vector<Point> getAllPos();

    void paintEvent(QPaintEvent *event);
private:
    Ui::MainWindow *ui;
    Point getCenterButton(QPushButton *button);

};

#endif // MAINWINDOW_H
