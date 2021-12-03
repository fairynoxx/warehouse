#ifndef SHELF_H
#define SHELF_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "package.h"

class Shelf : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Shelf(int, int, QObject *parent = nullptr, QGraphicsItem *parentPix = nullptr);
private:
    int posX;
    int posY;
    int unit;
    PackageType type;
    QMap<int, Package*> packages;
public:
    void addPackage(Package* pkg);
    Package* removePackage(int id);
signals:

};

#endif // SHELF_H
