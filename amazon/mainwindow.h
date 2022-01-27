#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "floor.h"
#include "shelf.h"
#include "robotsupervisor.h"
#include "supervisor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * \brief The MainWindow class
 * Main class of the visual interface of the program
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor of the class
     */
    MainWindow(QWidget *parent = nullptr);

    /*!
     * \brief Destructor of the class
     */
    ~MainWindow();

    /*!
     * \brief Initializes the floor of the warehouse
     */
    void initFloor(int, int);

private slots:

    /*!
     * \brief Action after clicking button Create
     */
    void on_pushButton_clicked();

    /*!
     * \brief Makes one step of the simulation periodically
     */
    void makeStep();

    /*!
     * \brief Randomly selects a package from available on shelves packages and tells Supervisor that the package has been requested
     */
    void newOrder();

    /*!
     * \brief Adds new package of random type periodically
     */
    void newPackage();

    /*!
     * \brief Checks if there are new orders periodically
     */
    void checkOrders();

    /*!
     * \brief Updates logs in user interface
     */
    void updateLogs(int, PackageType);
private:
    /*!
     * \brief Graphical user interface
     */
    Ui::MainWindow *ui;

    /*!
     * \brief Floor of the warehouse
     */
    class Floor *floorW;

    /*!
     * \brief Robot Supervisor
     */
    RobotSupervisor * RS;

    /*!
     * \brief Supervisor
     */
    Supervisor * S;

    /*!
     * \brief Number of packages in the warehouse
     */
    int numOfPackages = 0;

    /*!
     * \brief Is the interface created
     */
    bool isCreated = false;
    /*!
     * \brief Timer for making steps of simulation
     */
    QTimer * timer;

    /*!
     * \brief Timer for arriving a new package
     */
    QTimer * newPkgTimer;

    /*!
     * \brief Timer for creating new orders
     */
    QTimer * newOrderTimer;

    /*!
     * \brief Timer for checking if there are new packages
     */
    QTimer * checkPackagesTimer;

    /*!
     * \brief List of packages IDs on start
     */
    QList<int> startList;

    /*!
     * \brief List of packages IDs on the floor of the warehouse
     */
    QList<int> magList;

    /*!
     * \brief List of packages IDs on end shelf
     */
    QList<int> endList;
};
#endif // MAINWINDOW_H
