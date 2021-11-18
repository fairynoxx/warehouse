#include "robot.h"
#include <thread>
#include <chrono>


Robot::Robot(int x, int y, int scale, QObject *parent, QGraphicsItem *parentPix) : QObject(parent), QGraphicsPixmapItem(parentPix)
{
    posX = x;
    posY = y;
    unit = scale;
    setPixmap(QPixmap(":/images/robot.png"));
    this->setX(x*scale);
    this->setY(y*scale);
    this->setScale(double(unit)/500);
    this->setVisible(true);
    rotation = Direction::north;
    setFlag(ItemSendsGeometryChanges);
}

void Robot::rotateRobot(Direction d)
{
    if(d != rotation)
    {
        int temp = getRotations(d);
        if(temp > 0)
        {
            for(int i = 0; i < temp; i++) {
                this->setRotation(90);
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }
        else
        {
            this->setRotation(-90);
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    rotation = d;
}
void Robot::moveRobot(Direction d)
{
    rotateRobot(d);
    switch (d) {
    case Direction::north:
        posY = posY - 1;
        this->setY(posY*unit);
        break;
    case Direction::south:
        posY = posY + 1;
        this->setY(posY*unit);
        break;
    case Direction::east:
        posX = posX + 1;
        this->setX(posX*unit);
        break;
    case Direction::west:
        posX = posX - 1;
        this->setX(posX*unit);
        break;
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

bool Robot::isDirectionOpposite(Direction d)
{
    switch (d) {
    case Direction::north:
        if(rotation == Direction::south)
            return true;
        break;
    case Direction::south:
        if(rotation == Direction::north)
            return true;
        break;
    case Direction::east:
        if(rotation == Direction::west)
            return true;
        break;
    case Direction::west:
        if(rotation == Direction::east)
            return true;
        break;
    }
    return false;
}

int Robot::getRotations(Direction d)
{
    if(isDirectionOpposite(d))
        return 2;

    switch (d) {
    case Direction::north:
        if(rotation == Direction::west)
            return 1;
        else
            return -1;
        break;
    case Direction::south:
        if(rotation == Direction::east)
            return 1;
        else
            return -1;
        break;
    case Direction::east:
        if(rotation == Direction::north)
            return 1;
        else
            return -1;
        break;
    case Direction::west:
        if(rotation == Direction::south)
            return 1;
        else
            return -1;
        break;
    default:
        throw("ajajajaj");
    }
}
