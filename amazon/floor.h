#ifndef FLOOR_H
#define FLOOR_H

#include <QWidget>
#include <QPair>
#include <QPainter>
#include <QGraphicsScene>
#include "tile.h"
#include "robot.h"
#include "shelf.h"
#include <QQueue>

namespace Ui {
class Floor;
}

class Floor : public QWidget
{
    Q_OBJECT

public:
    explicit Floor(int sizeX, int sizeY, QWidget *parent = nullptr);
    ~Floor();
    void initFloor();
    QSize getsize();
    void setFloorSize(int,int);
    void addRobot(int,int);
    void moveRobot(Robot*, Direction);
    void addShelf(int, int, PackageType);
    void printShelves();
    ///// MOVE TO PRIVATE
    QMap<PackageType, QVector<Shelf*>> shelves;
    QVector<Robot*> robots;
    QQueue<Package*> newPackages;
    void addNewPackage(Package*);
    QVector<Package*> availablePackages(Shelf*);
    QPair<int, int> floorSize;
    QVector<QVector <Tile*>> tiles;
private:
    Ui::Floor *ui;
    int tileSize;
    QGraphicsScene *scene;
    void initializeShelves();
};


#endif // FLOOR_H
