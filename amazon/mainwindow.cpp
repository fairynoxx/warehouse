#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include "floor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBoxPackageType->addItem("category 1");
    ui->comboBoxPackageType->addItem("category 2");
    ui->comboBoxPackageType->addItem("category 3");
    ui->comboBoxPackageType->addItem("category 4");
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
    //QSize s = floorW->getsize();
    floorW->addRobot(5,5);
    floorW->addShelf(1,1,PackageType::cat1);
    floorW->addShelf(4,4,PackageType::cat2);
    floorW->addShelf(6,3,PackageType::cat3);
    floorW->addShelf(9,2,PackageType::cat4);
    floorW->addShelf(3,3,PackageType::cat3);
    floorW->printShelves();
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


void MainWindow::on_pushButtonCreatePackage_clicked()
{
    PackageType t;
    switch (ui->comboBoxPackageType->currentIndex()) {
    case 0:
        t = PackageType::cat1;
        break;
    case 1:
        t = PackageType::cat2;
        break;
    case 2:
        t = PackageType::cat3;
        break;
    case 3:
        t = PackageType::cat4;
        break;
    default:
        t = PackageType::cat1;
        break;
    }
    Package* pkg = new Package(numOfPackages, t);
    numOfPackages++;
    floorW->addNewPackage(pkg);
}

