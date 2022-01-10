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


int RobotSupervisor::chooseFreeRobot(QPair<int,int> r)
{
    QPair<int,int> pos;
    int distance = 1000;
    int robotId = -1;
    auto end = freeRobots.cend();
    for (auto a = freeRobots.cbegin(); a != end; ++a)
    {
        pos = a.value()->getCurrentPosition();
        if(distance > std::abs(pos.first - r.first) + std::abs(pos.second - r.second))
        {
            distance = std::abs(pos.first - r.first) + std::abs(pos.second - r.second);
            robotId = a.key();
        }
    }
    if(robotId != -1)
    {
        busyRobots.insert(robotId,freeRobots[robotId]);
        freeRobots.remove(robotId);
    }
    else
        qDebug() << "no free robots";
    return robotId;
}

QVector<QPair<int, int> > RobotSupervisor::findPath(QPair<int,int> p1, QPair<int,int> p2)
{
    QVector<QVector<int>> grid;
    AStar path(floor->floorSize.first, floor->floorSize.second);
    for (int i = 0; i < floor->floorSize.first; i++)
    {
        QVector<int> column;
        for (int j = 0; j < floor->floorSize.second; j++)
        {
            if(floor->tiles[i][j]->status == TileStatus::empty)
                column.push_back(1);
            else
                column.push_back(0);
        }
        grid.push_back(column);
    }
    path.aStarSearch(grid, p1, p2);
    return path.trace;
}

bool RobotSupervisor::sendRobot(QPair<int, int> destination)
{
    int robotId = chooseFreeRobot(destination);
    if (robotId != -1)
    {
        robotsPaths.insert(robotId, findPath(busyRobots.find(robotId).value()->getCurrentPosition(),destination));
        return true;
    }
    return false;
}

void RobotSupervisor::moveRobots()
{
    auto end = robotsPaths.cend();
    QVector<int> finishedRobots;
    for (auto a = robotsPaths.cbegin(); a != end; ++a)
    {
        busyRobots.find(a.key()).value()->moveRobotToCoordinates(a.value().front());
        robotsPaths[a.key()].pop_front();
        if(robotsPaths[a.key()].isEmpty())
        {
            freeRobots.insert(a.key(), busyRobots[a.key()]);
            busyRobots.remove(a.key());
            finishedRobots.push_back(a.key());

        }
        if(busyRobots.contains(a.key()))
            qDebug() << "id: " << a.key() << " -- " << busyRobots[a.key()]->posX << " " << busyRobots[a.key()]->posY;
    }
    for (auto a: finishedRobots)
        robotsPaths.remove(a);
}


