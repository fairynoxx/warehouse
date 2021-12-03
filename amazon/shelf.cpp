#include "shelf.h"

Shelf::Shelf(int x, int y, PackageType t, QObject *parent, QGraphicsItem *parentPix) : QObject(parent), QGraphicsPixmapItem(parentPix)
{
    posX = x;
    posY = y;
    type = t;
    setImage();
}

void Shelf::setImage()
{
    switch (type) {
    case PackageType::cat1:
        if(isShelfFull() == false)
            setPixmap(QPixmap(":/images/shelf_1_empty.png"));
        else
            setPixmap(QPixmap(":/images/shelf_1_full.png"));
        break;
    case PackageType::cat2:
        if(isShelfFull() == false)
            setPixmap(QPixmap(":/images/shelf_2_empty.png"));
        else
            setPixmap(QPixmap(":/images/shelf_2_full.png"));
        break;
    case PackageType::cat3:
        if(isShelfFull() == false)
            setPixmap(QPixmap(":/images/shelf_3_empty.png"));
        else
            setPixmap(QPixmap(":/images/shelf_3_full.png"));
        break;
    case PackageType::cat4:
        if(isShelfFull() == false)
            setPixmap(QPixmap(":/images/shelf_4_empty.png"));
        else
            setPixmap(QPixmap(":/images/shelf_4_full.png"));
        break;
    default:
        break;
    }
}


void Shelf::addPackage(Package *pkg)
{
    packages.insert(pkg->id, pkg);
    pkg->changeStatus(PackageStatus::delivered);
    if (packages.size() == MAX_PKGS)
        isFull = true;
    setImage();
}

Package *Shelf::removePackage(int id)
{
    Package *pkg = packages.take(id);
    pkg->changeStatus(PackageStatus::onTheWay);
    if (isFull == true)
        isFull = false;
    setImage();
    return pkg;
}

bool Shelf::isShelfFull()
{
    return isFull;
}