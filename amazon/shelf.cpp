#include "shelf.h"

Shelf::Shelf(int x, int y, PackageType t, QObject *parent, QGraphicsItem *parentPix) : QObject(parent), QGraphicsPixmapItem(parentPix)
{
    posX = x;
    posY = y;
    type = t;
    setImage();
//    if(t == PackageType::start || t == PackageType::end)
//          set some bigger MAX_PKGS
}

void Shelf::setImage()
{
    switch (type) {
    case PackageType::cat1:
        if(isShelfFull())
            setPixmap(QPixmap(":/images/shelf_1_full.png"));
        else if(isShelfEmpty())
            setPixmap(QPixmap(":/images/shelf_1_empty.png"));
        else
            setPixmap(QPixmap(":/images/shelf_1.png"));
        break;
    case PackageType::cat2:
        if(isShelfFull())
            setPixmap(QPixmap(":/images/shelf_2_full.png"));
        else if(isShelfEmpty())
            setPixmap(QPixmap(":/images/shelf_2_empty.png"));
        else
            setPixmap(QPixmap(":/images/shelf_2.png"));
        break;
    case PackageType::cat3:
        if(isShelfFull())
            setPixmap(QPixmap(":/images/shelf_3_full.png"));
        else if(isShelfEmpty())
            setPixmap(QPixmap(":/images/shelf_3_empty.png"));
        else
            setPixmap(QPixmap(":/images/shelf_3.png"));
        break;
    case PackageType::cat4:
        if(isShelfFull())
            setPixmap(QPixmap(":/images/shelf_4_full.png"));
        else if(isShelfEmpty())
            setPixmap(QPixmap(":/images/shelf_4_empty.png"));
        else
            setPixmap(QPixmap(":/images/shelf_4.png"));
        break;
    case PackageType::start:
        setPixmap(QPixmap(":/images/start_field.png"));
    default:
        break;
    }
}


void Shelf::addPackage(Package *pkg)
{
    packages.insert(pkg->id, pkg);
    pkg->changeStatus(PackageStatus::delivered);
    if (getShelfType()==PackageType::start)
    {
        isFull = false;
    }
    else
    {
        if (packages.size() == MAX_PKGS)
            isFull = true;
        if (isEmpty)
            isEmpty = false;
    }
    setImage();
}

Package* Shelf::removePackage(int id)
{
    Package *pkg = packages.take(id);
    pkg->changeStatus(PackageStatus::onTheWay);
    if (isFull)
        isFull = false;
    if (packages.size() == 0)
        isEmpty = true;
    setImage();
    return pkg;
}

bool Shelf::isShelfFull()
{
    return isFull;
}

bool Shelf::isShelfEmpty()
{
    return isEmpty;
}

QVector<Package*> Shelf::availablePackages()
{
    QVector<Package*> v;
    QList<Package*> l = packages.values();
    for (auto a: l)
        v.push_back(a);
    return v;
}

PackageType Shelf::getShelfType()
{
    return type;
}

bool Shelf::isThereAPackage(int id)
{
    if (packages.keys().contains(id))
        return true;
    return false;
}

QPair<int, int> Shelf::getShelfPosition()
{
    return QPair<int,int>(posX,posY);
}
