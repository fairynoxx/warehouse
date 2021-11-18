#include "robot.h"

Robot::Robot(int x, int y, int scale, QObject *parent, QGraphicsItem *parentPix) : QObject(parent), QGraphicsPixmapItem(parentPix)
{
    posX = x;
    posY = y;
    setPixmap(QPixmap(":/images/robot.png"));
    this->setX(x*scale);
    this->setY(y*scale);
    this->setScale(double(scale/500));
    setFlag(ItemSendsGeometryChanges);
}

void Robot::moveRobot(Direction d)
{
    if(d != rotation)
    {

    }

}
