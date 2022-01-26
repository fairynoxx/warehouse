#include "robot.h"
#include <thread>
#include <chrono>

/*!
 * \brief Constructor of the clas
 * Creates object robot with specified position
 * \param pos - position of the robot
 * \param scale - scale of the robot image
 * \param parent - parent
 * \param parentPix - pixmap of the parent
 */
Robot::Robot(QPair<int,int> pos, int scale, QObject *parent, QGraphicsItem *parentPix) : QObject(parent), QGraphicsPixmapItem(parentPix)
{
    position = pos;
    unit = scale;
    setPixmap(QPixmap(":/images/robot.png"));
    this->setX(pos.first*scale);
    this->setY(pos.second*scale);
    this->setScale(double(unit)/500);
    this->setVisible(true);
    orientation = Direction::north;
    this->pkg = nullptr;
}

/*!
 * \brief Rotates the robot to the specified orientation
 * \param d - target orientation
 */
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

/*!
 * \brief Moves robot to the field in target direction
 * \param d - target direction
 */
void Robot::moveRobot(Direction d)
{
    rotateRobot(d);
    switch (d) {
    case Direction::north:
        position.second = position.second - 1;
        this->setY(position.second*unit);
        break;
    case Direction::south:
        position.second = position.second + 1;
        this->setY(position.second*unit);
        break;
    case Direction::east:
        position.first = position.first + 1;
        this->setX(position.first*unit);
        break;
    case Direction::west:
        position.first = position.first - 1;
        this->setX(position.first*unit);
        break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

}

/*!
 * \brief Moves robot to target coordinates
 * \param pos - target position
 * \return true - if robot changed position, false if robot stayed in the same place
 */
bool Robot::moveRobotToCoordinates(QPair<int, int> pos)
{
    if(pos.first == position.first && pos.second == position.second)
        return false;
    Direction d;
    if(pos.first == position.first)
    {
        if(pos.second > position.second)
            d = Direction::south;
        else
            d = Direction::north;
    }
    else
    {
        if(pos.first > position.first)
            d = Direction::east;
        else
            d = Direction::west;
    }
    moveRobot(d);
    return true;
}

/*!
 * \brief Takes package from the shelf
 * \param p - pointer to the package
 */
void Robot::takePackage(Package* p)
{
    this->pkg = p;
    this->setPixmap(QPixmap(":/images/robot_pkg.png"));
    updateImgRotation();
}

/*!
 * \brief Leaves package on the shelf
 * \return pointer to the left package
 */
Package *Robot::leavePackage()
{
    this->setPixmap(QPixmap(":images/robot.png"));
    updateImgRotation();
    Package* p = this->pkg;
    this->pkg = nullptr;
    this->order = nullptr;
    return p;
}

/*!
 * \brief Gives the type of the package that robot is carrying
 * \return true - robot has package, false - robot does not have a package
 */
bool Robot::isBusy()
{
    if (this->pkg == nullptr)
        return false;
    return true;
}

/*!
 * \brief Gives current position of the robot
 * \return type of the package
 */
PackageType Robot::getPackageType()
{
    if (this->pkg != nullptr)
        return pkg->getPackageType();
    return PackageType::start;
}

/*!
 * \brief Gives current position of the robot
 * \return current position of the robot
 */
QPair<int, int> Robot::getCurrentPosition()
{
    QPair<int,int> p;
    p.first = position.first;
    p.second = position.second;
    return p;
}

/*!
 * \brief Assignes the order for robot to execute
 * \param o - pointer to the new order
 */
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
