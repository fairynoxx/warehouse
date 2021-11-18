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
    orientation = Direction::north;
}

void Robot::rotateRobot(Direction d)
{
    if(d != orientation)
    {
        int temp = getRotations(d);
        if(temp > 0)
        {
            for(int i = 0; i < temp; i++) {
                this->setRotation(rotation()+90);
                this->update();
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }
        else
        {
            this->setRotation(rotation()-90);
            this->update();

            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    orientation = d;
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
        if(orientation == Direction::south)
            return true;
        break;
    case Direction::south:
        if(orientation == Direction::north)
            return true;
        break;
    case Direction::east:
        if(orientation == Direction::west)
            return true;
        break;
    case Direction::west:
        if(orientation == Direction::east)
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
        if(orientation == Direction::west)
            return 1;
        else
            return -1;
        break;
    case Direction::south:
        if(orientation == Direction::east)
            return 1;
        else
            return -1;
        break;
    case Direction::east:
        if(orientation == Direction::north)
            return 1;
        else
            return -1;
        break;
    case Direction::west:
        if(orientation == Direction::south)
            return 1;
        else
            return -1;
        break;
    default:
        throw("ajajajaj");
    }
}
