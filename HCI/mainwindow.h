#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include "voronoi.h"
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
    vector<Site_2> getAllPos();

private:
    Ui::MainWindow *ui;
    Site_2 getCenterButton(QPushButton *button);
};

#endif // MAINWINDOW_H
