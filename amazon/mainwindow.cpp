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
    RS = new RobotSupervisor;
    S = new Supervisor;
    connect(S, &Supervisor::sendOrder, RS, &RobotSupervisor::sendRobot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initFloor(int sizeX, int sizeY)
{
   floorW = new class Floor(sizeX, sizeY, this);
   RS->floor = floorW;
   S->floor = floorW;
   this->ui->horizontalLayout_2->insertWidget(0, floorW);
}


void MainWindow::on_pushButton_clicked()
{
    initFloor(ui->spinBoxWidth->value(), ui->spinBoxHeight->value());
    floorW->setFloorSize(ui->spinBoxWidth->value(),ui->spinBoxHeight->value());
    QPair<int,int> start(5,0);
    floorW->initFloor(start);
    S->setStartTile(start);
    //QSize s = floorW->getsize();
    floorW->addRobot(5,5);
    floorW->addRobot(6,6);
    floorW->addRobot(7,7);
    RS->addRobot(floorW->robots[0]);
    RS->addRobot(floorW->robots[1]);
    RS->addRobot(floorW->robots[2]);
    S->addShelf(1,1,PackageType::cat1);
    S->addShelf(4,4,PackageType::cat2);
    S->addShelf(9,8,PackageType::cat2);
    S->addShelf(6,4,PackageType::cat3);
    S->addShelf(9,2,PackageType::cat4);
//    RS->sendRobot(QPair<int,int>(1,8));
//    RS->sendRobot(QPair<int,int>(9,9));
//    RS->sendRobot(QPair<int,int>(0,9));
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
    S->addPackage(t);
}

QVector<Shelf*> MainWindow::shelfNearRobot(Robot * r)
{
    QVector<Shelf*> v;
    for (auto &a: floorW->shelves)
    {
        for (auto b: a)
        {
            if (r->posX == b->posX)
                if (b->posY == r->posY - 1 || b->posY == r->posY + 1)
                    v.push_back(b);
            if (r->posY == b->posY)
                if (b->posX == r->posX - 1 || b->posX == r->posX + 1)
                    v.push_back(b);
        }
    }
    return v;
}

void MainWindow::checkForPackages(Robot * r)
{
    QVector<Shelf*> s = shelfNearRobot(r);
    ui->comboBoxAvailablePackages->clear();
    if (!s.isEmpty())
    {
        QVector<Package*> v;
        for (auto a: s)
        {
            v = floorW->availablePackages(a);
            for (auto b: v)
            {
                ui->comboBoxAvailablePackages->addItem(QString::number(b->id));
            }
        }
    }
}

void MainWindow::on_buttonTakePackage_clicked()
{
    QVector<Shelf*> s = shelfNearRobot(floorW->robots[0]);
    if (!s.isEmpty())
    {
        if (!floorW->robots[0]->isBusy())
        {
            for (auto a: s)
            {
                if(a->isThereAPackage(ui->comboBoxAvailablePackages->currentText().toInt()))
                {
                    floorW->robots[0]->takePackage(a->removePackage(ui->comboBoxAvailablePackages->currentText().toInt()));
                    break;
                }
            }
        }
        else
        {
            for (auto a: s)
            {
                if(floorW->robots[0]->getPackageType() == a->getShelfType())
                {
                    a->addPackage(floorW->robots[0]->leavePackage());
                    break;
                }
            }

        }
    }
    RS->moveRobots();
}


void MainWindow::on_pushButtonNewOrder_clicked()
{
    S->checkForOrders();
}

