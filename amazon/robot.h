#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <QGraphicsPixmapItem>

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
    int posX;
    int posY;
    int unit;
    Direction rotation;
    void rotateRobot(Direction);
    int getRotations(Direction);
    bool isDirectionOpposite(Direction);
public:
    void moveRobot(Direction);

signals:

};

#endif // ROBOT_H
