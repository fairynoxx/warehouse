#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include "floor.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initFloor(int sizeX, int sizeY)
{
   floorW = new class Floor(sizeX, sizeY,this);
   this->ui->horizontalLayout_2->insertWidget(0, floorW);
}


void MainWindow::on_pushButton_clicked()
{
    initFloor(ui->spinBoxWidth->value(),ui->spinBoxHeight->value());
    floorW->setFloorSize(ui->spinBoxWidth->value(),ui->spinBoxHeight->value());
    floorW->initFloor();
    QSize s = floorW->getsize();
    floorW->addRobot(5,5);

}

void MainWindow::on_buttonNorth_clicked()
{
    floorW->moveRobot(Direction::north);
}



void MainWindow::on_buttonSouth_clicked()
{
    floorW->moveRobot(Direction::south);

}


void MainWindow::on_buttonEast_clicked()
{
    floorW->moveRobot(Direction::east);
}


void MainWindow::on_buttonWest_clicked()
{
    floorW->moveRobot(Direction::west);
}

