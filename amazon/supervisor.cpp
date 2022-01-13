#include "supervisor.h"

Supervisor::Supervisor()
{

}

void Supervisor::addShelf(int x, int y, PackageType type)
{
    floor->addShelf(x, y, type);
}

void Supervisor::addPackage(PackageType type)
{
    Package* pkg = new Package(numOfPackages, type);
    numOfPackages++;
    packages.enqueue(pkg);
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
        floor->shelves[PackageType::start][0]->addPackage(packages.front());
        o->pkgId = packages.front()->id;
        o->posStart = startTile;
        o->posEnd = findShelfForPackage(o->pkgId, packages.front()->getPackageType());
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
            if(b->getShelfType() != PackageType::start && b->getShelfType() != PackageType::end)
            {
                pkgs = b->availablePackages();
                for(auto c: pkgs)
                    pkgIds.push_back(c->id);
            }
        }
    }
    return pkgIds;
}

QPair<int, int> Supervisor::findShelfForPackage(int pkgId, PackageType type)
{
    for (auto a: floor->shelves[type])
    {
        if(!a->isShelfFull())
        {
            qDebug() << "ale super polka omg " << a->posX << " " << a->posY;
            packagesOnShelves.insert(pkgId, a);
            return QPair<int,int>(a->posX,a->posY);
        }
    }
}


