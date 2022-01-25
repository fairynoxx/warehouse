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
    floor->tiles[r->getCurrentPosition().first][r->getCurrentPosition().second]->changeTileStatus(TileStatus::occupied);
}


int RobotSupervisor::chooseFreeRobot(QPair<int,int> r)
{
    QPair<int,int> pos;
    int distance = 1000;
    int robotId = -1;
    if (freeRobots.isEmpty())
    {
        qDebug() << "no free robots";
        return -1;
    }
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
    busyRobots.insert(robotId,freeRobots[robotId]);
    freeRobots.remove(robotId);
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
            if(floor->tiles[i][j]->getTileStatus() == TileStatus::empty)
                column.push_back(1);
            else
                column.push_back(0);
        }
        grid.push_back(column);
    }
    path.aStarSearch(grid, p1, p2);
    ////
    ///

//    for (int j = 0; j < floor->floorSize.second; j++)
//    {
//        QDebug deb = qDebug();
//        for (int i = 0; i < floor->floorSize.first ; i++)
//        {
//            deb << grid[i][j];
//        }
//        qDebug() << " ";
//    }
    //qDebug() << "start: " << p1.first << " " << p1.second << " end: " << p2.first << " " << p2.second;
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
                        r->pkg->changeStatus(PackageStatus::onTheWay);
                        //qDebug() << "robot collected package number " << r->order->pkgId;
                        return;
                }
                else
                    qDebug() << "there is no such package on the shelf";
            }
        }
    }
    qDebug() << "there is no shelf";
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
                r->pkg->changeStatus(PackageStatus::delivered);
               // qDebug() << "LEAVINGGGGG PKG: " << r->order << "SHELF POS: << " << b->posX << " " << b->posY;
                emit packageLeftOnShelf(r->order);
                b->addPackage(r->leavePackage());
                return;
            }
        }
    }
    qDebug() << "THERE IS NO GOOD SHELF" << r->order->posEnd.first << " " << r->order->posEnd.second;
}

void RobotSupervisor::sendRobot(Order* o)
{
    QPair<int,int> destination;
    //qDebug() << "POLE KONCOWE: " << o->posStart.first << " " << o->posStart.second;
    destination = determineEndField(o->posStart);
    int robotId = chooseFreeRobot(destination);
    if (robotId != -1)
    {
        busyRobots[robotId]->assignOrder(o);
        robotsWaiting.insert(robotId, 0);
        robotsPaths.insert(robotId, findPath(busyRobots.find(robotId).value()->getCurrentPosition(),destination));
        return;
    }
    emit orderNotAccepted(o);
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
            floor->tiles[busyRobots[a.key()]->getCurrentPosition().first][busyRobots[a.key()]->getCurrentPosition().second]->changeTileStatus(TileStatus::empty);
            if(!busyRobots.find(a.key()).value()->moveRobotToCoordinates(a.value().front()))
            {
                robotsWaiting[a.key()]++;
                floor->tiles[busyRobots[a.key()]->getCurrentPosition().first][busyRobots[a.key()]->getCurrentPosition().second]->changeTileStatus(TileStatus::occupied);
            }
            else
                robotsWaiting[a.key()] = 0;
            robotsPaths[a.key()].pop_front();
        }
        //floor->tiles[busyRobots[a.key()]->getCurrentPosition().first][busyRobots[a.key()]->getCurrentPosition().second]->changeTileStatus(TileStatus::occupied);
        if(robotsPaths[a.key()].isEmpty())
        {
            if(!busyRobots[a.key()]->isBusy())
            {
                collectThePackage(a.key());
               // qDebug() << "collecting package nr: " << busyRobots[a.key()]->order->pkgId << " robot id: " << a.key() << " robot pos: " << busyRobots[a.key()]->getCurrentPosition().first << " " << busyRobots[a.key()]->getCurrentPosition().second;
                sendRobotId(a.key(), busyRobots[a.key()]->order->posEnd);
            }
            else
            {
                QVector<QPair<int,int>> v = findNeighbourFields(busyRobots[a.key()]->getCurrentPosition());
                if (v.contains(busyRobots[a.key()]->order->posEnd))
                {
                   // qDebug() << "leaving package nr: " << busyRobots[a.key()]->order->pkgId << " robot id: " << a.key() << " robot pos: " << busyRobots[a.key()]->getCurrentPosition().first << " " << busyRobots[a.key()]->getCurrentPosition().second;
                    leavePackage(a.key());
                    freeRobots.insert(a.key(), busyRobots[a.key()]);
                    robotsWaiting.remove(a.key());
                    busyRobots.remove(a.key());
                    finishedRobots.push_back(a.key());
                }
                else
                {
                    sendRobotId(a.key(), busyRobots[a.key()]->order->posEnd);
                    if (robotsPaths[a.key()].isEmpty())
                        robotsPaths[a.key()].emplaceFront(busyRobots[a.key()]->getCurrentPosition());
                }

            }
        }        
    }
    for (auto a: finishedRobots)
    {
        robotsPaths.remove(a);
        floor->tiles[freeRobots[a]->getCurrentPosition().first][freeRobots[a]->getCurrentPosition().second]->changeTileStatus(TileStatus::occupied);
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
    if(checkForDeadlock())
        resolveDeadlock();
     printGrid();
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
                   //qDebug() << "COLLISION " << busyRobots[a.key()]->posX << busyRobots[a.key()]->posY << " and " << busyRobots[b.key()]->posX << " " << busyRobots[b.key()]->posY;
               }
               QPair<int,int> posA = busyRobots[a.key()]->getCurrentPosition();
               QPair<int,int> posB = busyRobots[b.key()]->getCurrentPosition();
               if(robotsPaths[a.key()][0] == posB && robotsPaths[b.key()][0] == posA)
               {
                   floor->tiles[posB.first][posB.second]->changeTileStatus(TileStatus::occupied);
                   sendRobotId(a.key(), busyRobots[a.key()]->order->posEnd);
                   floor->tiles[posB.first][posB.second]->changeTileStatus(TileStatus::empty);
               }
           }
       }
    }
}

bool RobotSupervisor::sendRobotId(int id, QPair<int, int> d)
{
    QPair<int,int> destination;
    destination = determineEndField(d);
    if(destination.first == -1)
    {
        robotsPaths[id].emplaceFront(busyRobots[id]->getCurrentPosition());
        return false;
    }
    robotsPaths[id].clear();
    robotsPaths[id] = findPath(busyRobots.find(id).value()->getCurrentPosition(),destination);
    return true;
}

QPair<int, int> RobotSupervisor::determineEndField(QPair<int, int> shelfPos)
{
    QVector<QPair<int,int>> allFields = findNeighbourFields(shelfPos);
    QVector<QPair<int,int>> v = findNeighbourFields(shelfPos);
    for (auto a: allFields)
        if (floor->tiles[a.first][a.second]->getTileStatus() == TileStatus::empty)
            v.push_back(a);
    if (v.isEmpty())
        return QPair<int,int>(-1, -1);
    return v[rand()%v.size()];
}

bool RobotSupervisor::checkForDeadlock()
{
    for (int &a: robotsWaiting.keys())
    {
        if(robotsWaiting[a] > 4)
        {
            return true;
        }
    }
    return false;
}

void RobotSupervisor::printGrid()
{
    QVector<QVector<int>> grid;
    for (int i = 0; i < floor->floorSize.first; i++)
    {
        QVector<int> column;
        for (int j = 0; j < floor->floorSize.second; j++)
        {
            column.push_back(0);
        }
        grid.push_back(column);
    }
    for (auto a: freeRobots.keys())
    {
        grid[freeRobots[a]->getCurrentPosition().first][freeRobots[a]->getCurrentPosition().second] = 1;
    }
    for (auto a: busyRobots.keys())
    {
        grid[busyRobots[a]->getCurrentPosition().first][busyRobots[a]->getCurrentPosition().second] = 2;
    }
    for (auto a: floor->shelves)
    {
        for(auto b: a)
        {
            grid[b->posX][b->posY] = 3;
        }
    }

    qDebug() << "grid: ";
    for (int j = 0; j < floor->floorSize.second; j++)
    {
        QDebug deb = qDebug();
        for (int i = 0; i < floor->floorSize.first ; i++)
        {
            deb << grid[i][j];
        }
        qDebug() << " ";
    }
}

QVector<QPair<int, int> > RobotSupervisor::findNeighbourFields(QPair<int, int> p)
{
    QVector<QPair<int,int>> v;
    for(int i = p.first - 1; i <= p.first + 1; i++)
    {
        for(int j = p.second - 1; j <= p.second + 1; j++)
        {
            if(i < floor->floorSize.first && i >= 0 && j < floor->floorSize.first && j >= 0)
            {
                if(i != p.first && j == p.second)
                {
                    v.push_back(QPair<int,int>(i,j));
                }
                if(i == p.first && j != p.second)
                {
                    v.push_back(QPair<int,int>(i,j));
                }
            }
        }
    }
    return v;
}

void RobotSupervisor::resolveDeadlock()
{
    for (auto a: busyRobots.keys())
    {
        floor->tiles[busyRobots[a]->getCurrentPosition().first][busyRobots[a]->getCurrentPosition().second]->changeTileStatus(TileStatus::occupied);
    }
    for (auto a: busyRobots.keys())
    {
        if(!busyRobots[a]->isBusy())
            sendRobotId(a, busyRobots[a]->order->posStart);
        else
            sendRobotId(a, busyRobots[a]->order->posEnd);
    }
}


