#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "package.h"

enum class Direction
{
    north,
    south,
    east,
    west
};

class Robot : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Robot(int, int, int, QObject *parent = nullptr, QGraphicsItem *parentPix = nullptr);
private:
    int unit;
    Direction orientation;
    void rotateRobot(Direction);
    int getRotations(Direction);
    bool isDirectionOpposite(Direction);
    Package* pkg;
    void updateImgRotation();
public:
    //// MOVE TO PRIVATE
    int posX;
    int posY;
    void moveRobot(Direction);
    void takePackage(Package* p);
    Package* leavePackage();
    bool isBusy();
    PackageType getPackageType();
signals:

};

#endif // ROBOT_H
