#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

vector<Point> MainWindow::getAllPos()
{
    vector<Point> PosButtons;

    PosButtons.push_back(getCenterButton(ui->pushButton));
    PosButtons.push_back(getCenterButton(ui->pushButton_2));
    PosButtons.push_back(getCenterButton(ui->pushButton_3));

    return PosButtons;
}



Point MainWindow::getCenterButton(QPushButton *button)
{


    int x =(button->pos().x() + button->pos().x()+button->width()) /2;
    int y =(button->pos().y() + button->pos().y()+button->width()) /2;

    Point pt=new Point(x,y); //= new Site_2();

    return pt;

}
