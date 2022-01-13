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
    //floor->tiles[r->getCurrentPosition().first][r->getCurrentPosition().second]->status = TileStatus::occupied;
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
        freeRobots[robotId]->setStatus(false);
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
    floor->tiles[p1.first][p1.second]->changeTileStatus(TileStatus::empty);
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
    ////
    ///

    for (int j = 0; j < floor->floorSize.second; j++)
    {
        QDebug deb = qDebug();
        for (int i = 0; i < floor->floorSize.first ; i++)
        {
            deb << grid[i][j];
        }
        qDebug() << " ";
    }
    qDebug() << "start: " << p1.first << " " << p1.second << " end: " << p2.first << " " << p2.second;
    return path.trace;
}

void RobotSupervisor::collectThePackage(int robotId)
{
    Robot* r = busyRobots[robotId];
    QVector<Shelf*> v;
    for (auto &a: floor->shelves)
    {
        for (auto &b: a)
        {
            if(b->posX == r->order->posStart.first && b->posY == r->order->posStart.second)
            {
                if(b->isThereAPackage(r->order->pkgId))
                {
                        r->takePackage(b->removePackage(r->order->pkgId));
                        qDebug() << "robot collected package number " << r->order->pkgId;
                        return;
                }
                else
                    qDebug() << "there is no such package on the shelf";
            }
            else
                qDebug() << "there is no shelf";
        }
    }
}

void RobotSupervisor::leavePackage(int robotId)
{
    Robot* r = busyRobots[robotId];
    for (auto &a: floor->shelves)
    {
        for (auto b: a)
        {
            if(b->posX == r->order->posEnd.first && b->posY == r->order->posEnd.second)
            {
                b->addPackage(r->leavePackage());
            }
        }
    }
}

bool RobotSupervisor::sendRobot(Order* o)
{
    QPair<int,int> destination;
    qDebug() << "POLE KONCOWE: " << o->posStart.first << " " << o->posStart.second;
    destination = determineEndField(o->posStart);
    int robotId = chooseFreeRobot(destination);
    if (robotId != -1)
    {
        busyRobots[robotId]->assignOrder(o);
        robotsPaths.insert(robotId, findPath(busyRobots.find(robotId).value()->getCurrentPosition(),destination));
        return true;
    }
    return false;
}

void RobotSupervisor::moveRobots()
{
    QVector<int> finishedRobots;
    robotsSynch();
    auto end = robotsPaths.cend();
    for (auto a = robotsPaths.cbegin(); a != end; ++a)
    {
        // crashes when robot is already on final tile
        //floor->tiles[busyRobots[a.key()]->getCurrentPosition().first][busyRobots[a.key()]->getCurrentPosition().second]->changeTileStatus(TileStatus::empty);
        if(!robotsPaths[a.key()].isEmpty())
        {
            busyRobots.find(a.key()).value()->moveRobotToCoordinates(a.value().front());
            robotsPaths[a.key()].pop_front();
        }
        //floor->tiles[busyRobots[a.key()]->getCurrentPosition().first][busyRobots[a.key()]->getCurrentPosition().second]->changeTileStatus(TileStatus::occupied);
        if(robotsPaths[a.key()].isEmpty())
        {
            if(!busyRobots[a.key()]->isBusy())
            {
                collectThePackage(a.key());
                sendRobotId(a.key(), busyRobots[a.key()]->order->posEnd);
            }
            else
            {
                leavePackage(a.key());
                freeRobots.insert(a.key(), busyRobots[a.key()]);
                busyRobots.remove(a.key());
                finishedRobots.push_back(a.key());
            }
        }        
    }
    for (auto a: finishedRobots)
    {
        robotsPaths.remove(a);
        floor->tiles[freeRobots[a]->getCurrentPosition().first][freeRobots[a]->getCurrentPosition().second]->changeTileStatus(TileStatus::occupied);
        freeRobots[a]->setStatus(true);
    }
    if(!finishedRobots.isEmpty())
    {
        for (auto c: busyRobots.keys())
        {
            if(!busyRobots[c]->isBusy())
                sendRobotId(c, busyRobots[c]->order->posStart);
            else
                sendRobotId(c, busyRobots[c]->order->posEnd);
        }
    }
}

void RobotSupervisor::robotsSynch()
{
    auto end = robotsPaths.cend();
    for (auto a = robotsPaths.cbegin(); a != end; ++a)
    {
       for (auto b = robotsPaths.cbegin(); b != end; b++)
       {
           if(a.key() != b.key() && !robotsPaths[a.key()].isEmpty() && !robotsPaths[b.key()].isEmpty())
           {
               if(robotsPaths[a.key()][0] == robotsPaths[b.key()][0])
               {
                   robotsPaths[b.key()].emplaceFront(busyRobots[b.key()]->getCurrentPosition());
               }
           }
       }
    }
}

bool RobotSupervisor::sendRobotId(int id, QPair<int, int> d)
{
    robotsPaths[id].clear();
    QPair<int,int> destination;
    destination = determineEndField(d);
    robotsPaths[id] = findPath(busyRobots.find(id).value()->getCurrentPosition(),destination);
    return true;
}

void RobotSupervisor::updateFieldsState()
{
    for (auto a: busyRobots.keys())
        floor->tiles[busyRobots[a]->getCurrentPosition().first][busyRobots[a]->getCurrentPosition().second]->changeTileStatus(TileStatus::occupied);
    for (auto a: freeRobots.keys())
        floor->tiles[freeRobots[a]->getCurrentPosition().first][freeRobots[a]->getCurrentPosition().second]->changeTileStatus(TileStatus::occupied);
}

QPair<int, int> RobotSupervisor::determineEndField(QPair<int, int> shelfPos)
{
    for(int i = shelfPos.first - 1; i <= shelfPos.first + 1; i++)
    {
        for(int j = shelfPos.second - 1; j <= shelfPos.second + 1; j++)
        {
            if(i < floor->floorSize.first && i >= 0 && j < floor->floorSize.first && j >= 0)
            {
                if(i != shelfPos.first)
                {
                    if(j == shelfPos.second && floor->tiles[i][j]->status == TileStatus::empty)
                        return QPair<int,int>(i,j);
                }
                if(j != shelfPos.second)
                {
                    if(i == shelfPos.first && floor->tiles[i][j]->status == TileStatus::empty)
                        return QPair<int,int>(i,j);
                }
            }
        }
    }
}


