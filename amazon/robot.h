#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "package.h"

/*!
 * \brief The Direction
 */
enum class Direction
{
    north,
    south,
    east,
    west
};

/*!
 * \brief Declaration of class Robot
 */
class Robot : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor of the class
     */
    explicit Robot(QPair<int,int>, int, QObject *parent = nullptr, QGraphicsItem *parentPix = nullptr);
private:
    /*!
     * \brief Unit of the scale of the images
     */
    int unit;

    /*!
     * \brief Current orientation of the robot
     */
    Direction orientation;

    /*!
     * \brief Current position of the robot
     */
    QPair<int,int> position;

    /*!
     * \brief Rotates the robot
     */
    void rotateRobot(Direction);

    /*!
     * \brief Gets number of rotations based on targed orientation
     */
    int getRotations(Direction);

    /*!
     * \brief Checks if direction of the robot is opposite to the target orientation
     */
    bool isDirectionOpposite(Direction);

    /*!
     * \brief Updates image of the robot based on current rotation
     */
    void updateImgRotation();

    /*!
     * \brief Moves robot to the field in target direction
     */
    void moveRobot(Direction);
public:
    /*!
     * \brief Package that is carried by the robot
     */
    Package* pkg;

    /*!
     * \brief Order that robot is executing
     */
    Order* order;

    /*!
     * \brief Moves robot to target coordinates
     */
    bool moveRobotToCoordinates(QPair<int,int>);

    /*!
     * \brief Takes package from the shelf
     */
    void takePackage(Package*);

    /*!
     * \brief Leaves package on the shelf
     */
    Package* leavePackage();

    /*!
     * \brief Gives the information if robot is carrying a package
     */
    bool isBusy();

    /*!
     * \brief Gives the type of the package that robot is carrying
     */
    PackageType getPackageType();

    /*!
     * \brief Gives current position of the robot
     */
    QPair<int,int> getCurrentPosition();

    /*!
     * \brief Assignes the order for robot to execute
     */
    void assignOrder(Order*);
};

#endif // ROBOT_H
