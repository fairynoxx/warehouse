#include "shelf.h"

Shelf::Shelf(int x, int y, QObject *parent, QGraphicsItem *parentPix) : QObject(parent), QGraphicsPixmapItem(parentPix)
{
    posX = x;
    posY = y;
    setPixmap(QPixmap(":/images/shelf.png"));
}

void Shelf::addPackage(Package *pkg)
{
    packages.insert(pkg->id, pkg);
    pkg->changeStatus(PackageStatus::delivered);
    if (packages.size() == MAX_PKGS)
        isFull = true;
}

Package *Shelf::removePackage(int id)
{
    Package *pkg = packages.take(id);
    pkg->changeStatus(PackageStatus::onTheWay);
    if (isFull == true)
        isFull = false;
    return pkg;
}

bool Shelf::isShelfFull()
{
    return isFull;
}
