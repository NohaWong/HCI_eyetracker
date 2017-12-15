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


    float x =(button->pos().x() + button->pos().x()+button->width()) /2.0;
    float y =(button->pos().y() + button->pos().y()+button->height()) /2.0;

    Point pt= Point( x,y);
    return pt;

}
void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);



    //On définit pour le QPainter un stylo rouge de taille 4
            QPen pen;
            pen.setColor (Qt::red);
            pen.setWidth (4);
            painter.setPen(pen);



            for(int i=4;i<v.cellules.size();i++)
            {
                Cellule *c=v.cellules[i];
                for(int j=0;j<c->sommets.size(); j++)
                {
                    Point p1 = c->sommets[j];
                    Point p2 = c->sommets[(j+1)%c->sommets.size()];
                    painter.drawLine(p1.x, p1.y, p2.x, p2.y);

                }
            }

}

