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
  //  PosButtons.push_back(getCenterButton(ui->pushButton_2));
  //  PosButtons.push_back(getCenterButton(ui->pushButton_3));

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

            //On dessine un rectangle
            //QPen : rouge de taille 4
            //QBrush : aucun remplissage
            painter.drawRect (10, 10, 80, 80);

            //On définit pour le QPainter un pinceau vert utilisant le pattern SOLID
            QBrush brush(Qt::SolidPattern);
            brush.setColor(Qt::green);
            painter.setBrush(brush);

            //On dessine un rectangle
            //QPen : rouge de taille 4
            //QBrush : remplissage vert avec le pattern SOLID
            painter.drawRect (15, 15, 70, 70);


            //On définit pour le QPainter stylo bleu de taille 8
            pen.setColor (Qt::blue);
            pen.setWidth (8);
            painter.setPen(pen);

            //Dessine une ligne
            //QPen : bleu de taille 8
            //QBrush : n'est pas utilisé pour une ligne
            painter.drawLine(0, 0, 100, 100);
}
