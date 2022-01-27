#ifndef ROBOTSUPERVISOR_H
#define ROBOTSUPERVISOR_H

#include <QVector>
#include "robot.h"
#include <QPair>
#include "floor.h"

/*!
 * \brief The RobotSupervisor class
 * Manages the robots on the floor of the warehouse, assigns orders from Supervisor to robots
 */
class RobotSupervisor : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor of the class
     */
    RobotSupervisor();

    /*!
     * \brief Adds robot to the warehouse
     */
    void addRobot(Robot*);

    /*!
     * \brief Moves all the robots (one step)
     */
    void moveRobots();

    /*!
     * \brief Pointer to the class floor that contains all the tiles and shelves in the warehouse
     */
    class Floor* floor;
public slots:
    /*!
     * \brief Assigns robot to execute the order
     */
    void sendRobot(Order*);
signals:
    /*!
     * \brief Gives information to the Supervisor that the order was not assigned due to lack of the free robots
     */
    void orderNotAccepted(Order*);

    /*!
     * \brief Gives information to the Supervisor that the package was delivered
     */
    void packageLeftOnShelf(Order*);
private:
    /*!
     * \brief Number of robots on the Floor
     */
    int numOfRobots = 0;

    /*!
     * \brief Map of free robots (key - ID of the robot, value - pointer to a robot)
     */
    QMap<int, Robot*> freeRobots;

    /*!
     * \brief Map of busy robots (key - ID of the robot, value - pointer to a robot)
     */
    QMap<int, Robot*> busyRobots;

    /*!
     * \brief Map of calculated paths for busy robots (key - ID of the robot, value - vector of fields coordinates)
     */
    QMap<int, QVector<QPair<int,int>>> robotsPaths;

    /*!
     * \brief Map of robots that cannot perform a move or calculate path, because the targed shelf has no free tiles around (key - ID of the robot, value - number of turns that robot waited)
     */
    QMap<int,int> robotsWaiting;

    /*!
     * \brief Orders robot to leave the package on shelf
     */
    void leavePackage(int);

    /*!
     * \brief Orders robot to collect the package from shelf
     */
    void collectThePackage(int);

    /*!
     * \brief Chooses the closest robot to the start field taken from order
     */
    int chooseFreeRobot(QPair<int,int>);

    /*!
     * \brief Finds path between two fields using A* algorithm
     */
    QVector<QPair<int,int>> findPath(QPair<int,int>, QPair<int,int>);

    /*!
     * \brief Synchronizes the robots to avoid collisions
     */
    void robotsSynch();

    /*!
     * \brief Sends particular robot to target field (used for recalculating path)
     */
    bool sendRobotId(int, QPair<int,int>);

    /*!
     * \brief Determines field near shelf based on its position
     */
    QPair<int,int> determineEndField(QPair<int,int>);

    /*!
     * \brief Checks if there occurs some deadlock and robots cannot move
     */
    bool checkForDeadlock();

    /*!
     * \brief Finds fields next to given field
     */
    QVector<QPair<int,int>> findNeighbourFields(QPair<int,int>);

    /*!
     * \brief Resolves deadlocks - recalculates paths for all robots
     */
    void resolveDeadlock();
};

#endif // ROBOTSUPERVISOR_H
