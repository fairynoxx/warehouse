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
    floor->shelves[PackageType::start][0]->addPackage(pkg);
}


void Supervisor::setStartTile(QPair<int, int> p)
{
    startTile = p;
    floor->addShelf(p.first, p.second, PackageType::start);
}

void Supervisor::checkForOrders()
{
    if(!floor->shelves[PackageType::start][0]->isShelfEmpty())
    {
        Order* o = new Order;
        o->pkgId = floor->shelves[PackageType::start][0]->availablePackages().first()->id;
        o->posStart = startTile;
        o->posEnd = findShelfForPackage(floor->shelves[PackageType::start][0]->availablePackages().first()->getPackageType());
        emit sendOrder(o);
    }
}

QPair<int, int> Supervisor::findShelfForPackage(PackageType type)
{
    for (auto a: floor->shelves[type])
    {
        if(!a->isShelfFull())
        {
            qDebug() << "ale super polka omg " << a->posX << " " << a->posY;
            return QPair<int,int>(a->posX,a->posY);
        }
    }
}


