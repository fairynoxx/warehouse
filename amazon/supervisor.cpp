#include "supervisor.h"

/*!
 * \brief Constructor of the class
 */
Supervisor::Supervisor()
{

}

/*!
 * \brief Adds shelf to the warehouse
 * \param x - x coordinate of position
 * \param y - y coordinate of position
 * \param type - type of the shelf
 */
void Supervisor::addShelf(int x, int y, PackageType type)
{
    floor->addShelf(x, y, type);
    stateOfShelves.insert(QPair<int,int>(x,y),0);
}

/*!
 * \brief Creates new package
 * \param type - type of package
 * \return ID of the package
 */
int Supervisor::addPackage(PackageType type)
{
    Package* pkg = new Package(numOfPackages, type);
    numOfPackages++;
    allPackages.insert(pkg->getPackageId(), pkg);
    packages.enqueue(pkg);
    return pkg->getPackageId();
}

/*!
 * \brief Sets start shelf of the warehouse
 * \param p - position of the start shelf
 */
void Supervisor::setStartTile(QPair<int, int> p)
{
    startTile = p;
    floor->addShelf(p.first, p.second, PackageType::start);
}

/*!
 * \brief Sets end shelf of the warehouse
 * \param p - position of end shelf
 */
void Supervisor::setEndTile(QPair<int, int> p)
{
    endTile = p;
    floor->addShelf(p.first, p.second, PackageType::end);
}

/*!
 * \brief Checks if there are new packages waiting and prepares an order
 * If there are packages waiting chooses the first package, finds shelf for it.
 * If there are no free shelves, puts package at the end of the queue.
 * If there are free shelves sends an order to Robot Supervisor
 */
void Supervisor::checkForOrders()
{
    if(!packages.isEmpty())
    {
        Order* o = new Order;
        o->pkgId = packages.front()->getPackageId();
        o->posStart = startTile;
        o->posEnd = findShelfForPackage(o->pkgId, packages.front()->getPackageType());
        if(o->posEnd.first == -1)
        {
            delete o;
            qDebug() << "no free shelf";
            Package* p = packages.front();
            packages.pop_front();
            packages.enqueue(p);
            return;
        }
        floor->shelves[PackageType::start][0]->addPackage(packages.front());
        packages.front()->changeStatus(PackageStatus::waiting);
        packages.pop_front();
        emit sendOrder(o);
    }
}

/*!
 * \brief Prepares an order for requested package
 * \param pkgId - ID of the package
 */
void Supervisor::packageRequested(int pkgId)
{
    Order* o = new Order;
    o->pkgId = pkgId;
    o->posStart = packagesOnShelves[pkgId]->getShelfPosition();
    o->posEnd = endTile;
    allPackages[o->pkgId]->changeStatus(PackageStatus::waiting);
    emit sendOrder(o);
}

/*!
 * \brief Gives vector of IDs of all available packages on shelves (excluding start and end)
 * \return
 */
QVector<int> Supervisor::getPackagesOnShelves()
{
    QVector<int> ids;
    QVector<int> packages;
    for (auto a: floor->shelves)
    {
        for (auto b: a)
        {
            PackageType type = b->getShelfType();
            if(type != PackageType::start && type != PackageType::end)
            {
                packages = b->getAvailablePackages();
                ids.append(packages);
            }
        }
    }
    return ids;
}

/*!
 * \brief Gives position of the free shelf of particular type
 *  Adds package ID and shelf to the packagesOnShelves
 * \param pkgId - ID of the pacakge
 * \param type - type of the package
 * \return position of the chosen shelf - if (-1,-1) there are no free shelves
 */
QPair<int, int> Supervisor::findShelfForPackage(int pkgId, PackageType type)
{
    for (auto a: floor->shelves[type])
    {
        if(stateOfShelves[QPair<int,int>(a->posX, a->posY)] < MAX_PKGS)
        {
            QPair<int,int> pos(a->posX,a->posY);
            stateOfShelves[pos]++;
            packagesOnShelves.insert(pkgId, a);
            return pos;
        }
    }
    return QPair<int,int>(-1,-1);
}

/*!
 * \brief Cancels the order when RobotSupervisor gives the signal that there are no free robots
 * Removes package from packagesOnShelves and status of the package from waiting to delivered
 * \param o - order that is cancelled
 */
void Supervisor::cancelOrder(Order * o)
{
    if (o->posStart == startTile)
    {
        allPackages[o->pkgId]->changeStatus(PackageStatus::delivered);
        stateOfShelves[o->posEnd]--;
        packagesOnShelves.remove(o->pkgId);
    }
    else
    {
        allPackages[o->pkgId]->changeStatus(PackageStatus::delivered);
    }
}

/*!
 * \brief Completes the order
 * Updates state of the shelves and sends signal to update the logs
 * \param o
 */
void Supervisor::orderCompleted(Order* o)
{
    if (o->posEnd == endTile)
    {
        packagesOnShelves[o->pkgId] = floor->shelves[PackageType::end][0];
        stateOfShelves[o->posStart]--;
        emit updateLogs(o->pkgId, PackageType::end);
    }
    else
    {
        emit updateLogs(o->pkgId, PackageType::cat1);
    }
}


