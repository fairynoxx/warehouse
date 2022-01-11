#ifndef ROBOTSUPERVISOR_H
#define ROBOTSUPERVISOR_H

#include <QVector>
#include "robot.h"
#include <QPair>
#include "floor.h"


class RobotSupervisor
{
public:
    RobotSupervisor();
    void addRobot(Robot*);
    int chooseFreeRobot(QPair<int,int>); // pozycja do ktorej bedzie jechal
    QVector<QPair<int,int>> findPath(QPair<int,int>, QPair<int,int>);
    class Floor* floor;
    bool sendRobot(QPair<int,int>);
    void moveRobots();
private:
    int numOfRobots = 0;
    QMap<int, Robot*> freeRobots;
    QMap<int, Robot*> busyRobots;
    QMap<int, QVector<QPair<int,int>>> robotsPaths;
    void robotsSynch();
    bool sendRobotId(int, QPair<int,int>);
    void updateFieldsState();
};

#endif // ROBOTSUPERVISOR_H
