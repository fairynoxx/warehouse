#include "supervisor.h"

Supervisor::Supervisor()
{

}

void Supervisor::addShelf(int x, int y, PackageType type)
{
    floor->addShelf(x, y, type);
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
            qDebug() << "no free shelf";
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
                qDebug() << "shelf on: " << b->posX << " " << b->posY;
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
        if(!a->isShelfFull())
        {
            //qDebug() << "ale super polka omg " << a->posX << " " << a->posY;
            packagesOnShelves.insert(pkgId, a);

            return QPair<int,int>(a->posX,a->posY);
        }
    }
    return QPair<int,int>(-1,-1);
}

void Supervisor::cancelOrder(Order * o)
{
    if (o->posStart.first == startTile.first && o->posStart.second == startTile.first)
    {
        allPackages[o->pkgId]->changeStatus(PackageStatus::delivered);
        packagesOnShelves.remove(o->pkgId);
    }
    else
    {
        allPackages[o->pkgId]->changeStatus(PackageStatus::delivered);
    }
}

void Supervisor::orderCompleted(Order* o)
{
    if (o->posEnd.first == endTile.first && o->posEnd.second == endTile.second)
    {
        packagesOnShelves[o->pkgId] = floor->shelves[PackageType::end][0];
        emit updateLogs(o->pkgId, PackageType::end);
    }
    else
        emit updateLogs(o->pkgId, PackageType::cat1);
}


