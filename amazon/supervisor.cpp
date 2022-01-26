#include "supervisor.h"

Supervisor::Supervisor()
{

}

void Supervisor::addShelf(int x, int y, PackageType type)
{
    floor->addShelf(x, y, type);
    stateOfShelves.insert(QPair<int,int>(x,y),0);
}

int Supervisor::addPackage(PackageType type)
{
    Package* pkg = new Package(numOfPackages, type);
    numOfPackages++;
    allPackages.insert(pkg->getPackageId(), pkg);
    packages.enqueue(pkg);
    return pkg->getPackageId();
    //floor->shelves[PackageType::start][0]->addPackage(pkg);
}


void Supervisor::setStartTile(QPair<int, int> p)
{
    startTile = p;
    floor->addShelf(p.first, p.second, PackageType::start);
}

void Supervisor::setEndTile(QPair<int, int> p)
{
    endTile = p;
    floor->addShelf(p.first, p.second, PackageType::end);
}

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
            //qDebug() << "no free shelf";
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

void Supervisor::packageRequested(int pkgId)
{
    Order* o = new Order;
    o->pkgId = pkgId;
    o->posStart = packagesOnShelves[pkgId]->getShelfPosition();
    o->posEnd = endTile;
    allPackages[o->pkgId]->changeStatus(PackageStatus::waiting);
    emit sendOrder(o);
}

QVector<int> Supervisor::updateShelves()
{
    QVector<int> pkgIds;
    QVector<Package*> pkgs;
    for(auto &a: floor->shelves)
    {
        for(auto b: a)
        {
            QDebug deb = qDebug();
            if(b->getShelfType() != PackageType::start && b->getShelfType() != PackageType::end)
            {
                //qDebug() << "shelf on: " << b->posX << " " << b->posY;
                pkgs = b->getAllPackages();
                for(auto c: pkgs)
                {
                    pkgIds.push_back(c->getPackageId());
                    deb << c->getPackageId();
                }
            }
        }
    }
    return pkgIds;
}

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

QPair<int, int> Supervisor::findShelfForPackage(int pkgId, PackageType type)
{
    for (auto a: floor->shelves[type])
    {
        if(stateOfShelves[QPair<int,int>(a->posX, a->posY)] < MAX_PKGS)
        {
            //qDebug() << "ale super polka omg " << a->posX << " " << a->posY;
            QPair<int,int> pos(a->posX,a->posY);
            stateOfShelves[pos]++;
            packagesOnShelves.insert(pkgId, a);
            return pos;
        }
    }
    return QPair<int,int>(-1,-1);
}

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


