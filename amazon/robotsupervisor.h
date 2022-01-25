#ifndef ROBOTSUPERVISOR_H
#define ROBOTSUPERVISOR_H

#include <QVector>
#include "robot.h"
#include <QPair>
#include "floor.h"


class RobotSupervisor : public QObject
{
    Q_OBJECT
public:
    RobotSupervisor();
    void addRobot(Robot*);
    void moveRobots();
    class Floor* floor;
public slots:
    void sendRobot(Order*);
signals:
    void orderNotAccepted(Order*);
    void packageLeftOnShelf(Order*);
private:
    int numOfRobots = 0;
    QMap<int, Robot*> freeRobots;
    QMap<int, Robot*> busyRobots;
    QMap<int, QVector<QPair<int,int>>> robotsPaths;
    QMap<int,int> robotsWaiting;
    void leavePackage(int);
    void collectThePackage(int);
    int chooseFreeRobot(QPair<int,int>); // pozycja do ktorej bedzie jechal
    QVector<QPair<int,int>> findPath(QPair<int,int>, QPair<int,int>);
    void robotsSynch();
    bool sendRobotId(int, QPair<int,int>);
    QPair<int,int> determineEndField(QPair<int,int>);
    bool checkForDeadlock();
    void printGrid();
    QVector<QPair<int,int>> findNeighbourFields(QPair<int,int>);
    void resolveDeadlock();
};

#endif // ROBOTSUPERVISOR_H
