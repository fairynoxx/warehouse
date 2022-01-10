#include "robotsupervisor.h"
#include "math.h"
#include <QDebug>
#include "astar.cpp"

RobotSupervisor::RobotSupervisor()
{

}

void RobotSupervisor::addRobot(Robot * r)
{
    freeRobots.insert(numOfRobots, r);
    numOfRobots++;
}


Robot *RobotSupervisor::chooseFreeRobot(int x, int y)
{
    QPair<int,int> pos;
    int distance = 1000;
    Robot* closestRobot = nullptr;
    int robotId = -1;
    auto end = freeRobots.cend();
    for (auto a = freeRobots.cbegin(); a != end; ++a)
    {
        pos = a.value()->getCurrentPosition();
        if(distance > std::abs(pos.first - x) + std::abs(pos.second - y))
        {
            distance = std::abs(pos.first - x) + std::abs(pos.second - y);
            robotId = a.key();
        }
    }
    if(robotId != -1)
    {
        closestRobot = freeRobots[robotId];
        qDebug() << "id: " << robotId << " position: " << closestRobot->posX << " " << closestRobot->posY;
        busyRobots.insert(robotId,freeRobots[robotId]);
        freeRobots.remove(robotId);
    }
    else
        qDebug() << "no free robots";
    return closestRobot;
}

QVector<QPair<int, int> > RobotSupervisor::findPath(int, int, int, int)
{

}


