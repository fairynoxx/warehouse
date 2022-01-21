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
    this->pkg = nullptr;
}

void Robot::rotateRobot(Direction d)
{
    if(d != orientation)
    {
        int temp = getRotations(d);
        if(temp > 0)
        {
            for(int i = 0; i < temp; i++) {
                QPixmap p2 = this->pixmap().transformed(QTransform().rotate(90));
                this->setPixmap(p2);
                this->update();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
        else
        {
            QPixmap p2 = this->pixmap().transformed(QTransform().rotate(-90));
            this->setPixmap(p2);
            this->update();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

}

bool Robot::moveRobotToCoordinates(QPair<int, int> pos)
{
    if(pos.first == posX && pos.second == posY)
        return false;
    Direction d;
    if(pos.first == posX)
    {
        if(pos.second > posY)
            d = Direction::south;
        else
            d = Direction::north;
    }
    else
    {
        if(pos.first > posX)
            d = Direction::east;
        else
            d = Direction::west;
    }
    moveRobot(d);
    return true;
}

void Robot::takePackage(Package* p)
{
    this->pkg = p;
    this->setPixmap(QPixmap(":/images/robot_pkg.png"));
    updateImgRotation();
}

Package *Robot::leavePackage()
{
    this->setPixmap(QPixmap(":images/robot.png"));
    updateImgRotation();
    Package* p = this->pkg;
    this->pkg = nullptr;
    this->order = nullptr;
    return p;
}

bool Robot::isBusy()
{
    if (this->pkg == nullptr)
        return false;
    return true;
}

PackageType Robot::getPackageType()
{
    if (this->pkg != nullptr)
        return pkg->getPackageType();
    return PackageType::start;
}

bool Robot::getStatus()
{
    return(arrived);
}

void Robot::setStatus(bool status)
{
    arrived = status;
}

QPair<int, int> Robot::getCurrentPosition()
{
    QPair<int,int> p;
    p.first = posX;
    p.second = posY;
    return p;
}

void Robot::assignOrder(Order* o)
{
    order = o;
}

void Robot::updateImgRotation()
{
    QPixmap p2;
    switch (orientation) {
    case Direction::east:
        p2 = this->pixmap().transformed(QTransform().rotate(90));
        this->setPixmap(p2);
        break;
    case Direction::west:
        p2 = this->pixmap().transformed(QTransform().rotate(-90));
        this->setPixmap(p2);
        break;
    case Direction::south:
        p2 = this->pixmap().transformed(QTransform().rotate(180));
        this->setPixmap(p2);
        break;
    default:
        break;
    }
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
