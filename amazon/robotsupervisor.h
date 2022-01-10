#ifndef ROBOTSUPERVISOR_H
#define ROBOTSUPERVISOR_H

#include <QVector>
#include "robot.h"
#include <QPair>

class RobotSupervisor
{
public:
    RobotSupervisor();
    void addRobot(Robot*);
    Robot* chooseFreeRobot(int, int); // pozycja do ktorej bedzie jechal
private:
    int numOfRobots = 0;
    QMap<int, Robot*> freeRobots;
    QMap<int, Robot*> busyRobots;
    QVector<QPair<int,int>> findPath(int, int, int, int);
};

#endif // ROBOTSUPERVISOR_H
