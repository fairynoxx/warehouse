#ifndef SHELF_H
#define SHELF_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "package.h"

#define MAX_PKGS 2

class Shelf : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Shelf(int, int, PackageType, QObject *parent = nullptr, QGraphicsItem *parentPix = nullptr);
private:
    int unit;
    bool isFull = false;
    bool isEmpty = true;
    PackageType type;
    QMap<int, Package*> packages;
    void setImage();
public:
    //// TODO move to private
    int posX;
    int posY;
    //////
    void addPackage(Package* pkg);
    Package* removePackage(int id);
    bool isShelfFull();
    bool isShelfEmpty();
    QVector<Package*> getAllPackages();
    QVector<int> getAvailablePackages();
    PackageType getShelfType();
    bool isThereAPackage(int);
    QPair<int,int> getShelfPosition();
    void changePackageStatus(int, PackageStatus);
signals:

};

#endif // SHELF_H
