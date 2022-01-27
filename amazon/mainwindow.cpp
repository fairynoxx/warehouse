#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include "floor.h"
#include <QScrollBar>

/*!
 * \brief Constructor of the class
 * Creates Supervisor and RobotSupervisor, connects signals and slots, initializes UI
 * \param parent - parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RS = new RobotSupervisor;
    S = new Supervisor;
    connect(S, &Supervisor::sendOrder, RS, &RobotSupervisor::sendRobot);
    connect(RS, &RobotSupervisor::orderNotAccepted, S, &Supervisor::cancelOrder);
    connect(RS, &RobotSupervisor::packageLeftOnShelf, S, &Supervisor::orderCompleted);
    connect(S, &Supervisor::updateLogs, this, &MainWindow::updateLogs);
}

/*!
 * \brief Destructor of the class
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * \brief Initializes the floor of the warehouse
 * \param sizeX - width of the warehouse
 * \param sizeY - height of the warehouse
 */
void MainWindow::initFloor(int sizeX, int sizeY)
{
   floorW = new class Floor(sizeX, sizeY, this);
   RS->floor = floorW;
   S->floor = floorW;
   this->ui->horizontalLayout->insertWidget(0, floorW);
}

/*!
 * \brief Action after clicking button Create
 * Creates the floor based on size of the warehouse, adds robots and shelves, initializes timers for actions
 */
void MainWindow::on_pushButton_clicked()
{
    if (isCreated)
        return;
    initFloor(ui->spinBoxWidth->value(), ui->spinBoxHeight->value());
    floorW->setFloorSize(ui->spinBoxWidth->value(),ui->spinBoxHeight->value());
    QPair<int,int> start(0,std::round(ui->spinBoxHeight->value()/2));
    QPair<int,int> end(ui->spinBoxWidth->value()-1,std::round(ui->spinBoxHeight->value()/2));
    floorW->initFloor(start, end);
    S->setStartTile(start);
    S->setEndTile(end);
    floorW->addRobot(QPair<int,int>(5,5));
    floorW->addRobot(QPair<int,int>(6,6));
    floorW->addRobot(QPair<int,int>(7,7));
    floorW->addRobot(QPair<int,int>(8,8));
    floorW->addRobot(QPair<int,int>(0,7));
    floorW->addRobot(QPair<int,int>(0,6));
    RS->addRobot(floorW->robots[0]);
    RS->addRobot(floorW->robots[1]);
    RS->addRobot(floorW->robots[2]);
    RS->addRobot(floorW->robots[3]);
    RS->addRobot(floorW->robots[4]);
    RS->addRobot(floorW->robots[5]);

    S->addShelf(1,1,PackageType::cat1);
    S->addShelf(4,1,PackageType::cat2);
    S->addShelf(7,1,PackageType::cat2);
    S->addShelf(1,8,PackageType::cat3);
    S->addShelf(4,8,PackageType::cat4);
    S->addShelf(7,8,PackageType::cat4);

    timer = new QTimer(this);
    newPkgTimer = new QTimer(this);
    newOrderTimer = new QTimer(this);
    checkPackagesTimer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(makeStep()));
    connect(newPkgTimer, SIGNAL(timeout()), this, SLOT(newPackage()));
    connect(newOrderTimer, SIGNAL(timeout()), this, SLOT(newOrder()));
    connect(checkPackagesTimer, SIGNAL(timeout()), this, SLOT(checkOrders()));

    timer->start(500);
    newPkgTimer->start(2000);
    newOrderTimer->start(5000);
    checkPackagesTimer->start(500);
    isCreated = true;
}

/*!
 * \brief Makes one step of the simulation periodically
 */
void MainWindow::makeStep()
{
    RS->moveRobots();
}

/*!
 * \brief Updates logs in user interface based on package from completed order
 * \param id - ID of package
 * \param type - type of the package
 */
void MainWindow::updateLogs(int id, PackageType type)
{
    ui->logWindowMag->clear();
    ui->logWindowStart->clear();
    ui->logWindowsEnd->clear();
    switch (type) {
    case PackageType::start:
        startList.append(id);
        break;
    case PackageType::end:
        endList.append(id);
        magList.removeOne(id);
        break;
    default:
        magList.append(id);
        startList.removeOne(id);
        break;
    }

    for(auto a: startList)
    {
        ui->logWindowStart->appendPlainText(QString::number(a));
    }
    for(auto a: magList)
    {
        ui->logWindowMag->appendPlainText(QString::number(a));
    }
    for(auto a: endList)
    {
        ui->logWindowsEnd->appendPlainText(QString::number(a));
    }
    ui->logWindowStart->verticalScrollBar()->setValue(ui->logWindowStart->verticalScrollBar()->maximum());
    ui->logWindowMag->verticalScrollBar()->setValue(ui->logWindowMag->verticalScrollBar()->maximum());
    ui->logWindowsEnd->verticalScrollBar()->setValue(ui->logWindowsEnd->verticalScrollBar()->maximum());

}

/*!
 * \brief Randomly selects a package from available on shelves packages and tells Supervisor that the package has been requested
 * \param id - ID of the package
 * \param type - type of the package
 */
void MainWindow::newOrder()
{
    QVector<int> packages = S->getPackagesOnShelves();
    numOfPackages = packages.size();
    if(numOfPackages == 0)
        return;
    int chosenPackage = rand() % numOfPackages;
    S->packageRequested(packages[chosenPackage]);
}

/*!
 * \brief Adds new package of random type periodically
 */
void MainWindow::newPackage()
{
    PackageType t;
    switch (rand()%4) {
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
    updateLogs(S->addPackage(t), PackageType::start);
}

/*!
 * \brief Checks if there are new orders periodically
 */
void MainWindow::checkOrders()
{
    S->checkForOrders();
}

