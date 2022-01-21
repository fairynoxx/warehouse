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
    void updateImgRotation();
    bool arrived = false;
public:
    Package* pkg;
    //// MOVE TO PRIVATE
    int posX;
    int posY;
    Order* order;
    void moveRobot(Direction);
    bool moveRobotToCoordinates(QPair<int,int>);
    void takePackage(Package* p);
    Package* leavePackage();
    bool isBusy();
    PackageType getPackageType();
    bool getStatus();
    void setStatus(bool);
    QPair<int,int> getCurrentPosition();
    void assignOrder(Order*);
signals:

};

#endif // ROBOT_H
