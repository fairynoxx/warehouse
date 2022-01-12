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
}


void Supervisor::setStartTile(QPair<int, int> p)
{
    startTile = p;
    floor->addShelf(p.first, p.second, PackageType::start);
}

void Supervisor::checkForOrders()
{
    if(!packages.isEmpty())
    {
        Order* o = new Order;
        o->position = startTile;
        o->pkgId = packages.first()->id;
        emit sendOrder(o);
    }
}
