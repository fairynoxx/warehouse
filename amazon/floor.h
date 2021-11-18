#ifndef FLOOR_H
#define FLOOR_H

#include <QWidget>
#include <QPair>
#include <QPainter>
#include <QGraphicsScene>
#include "tile.h"
#include "robot.h"

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

private:
    Ui::Floor *ui;
    int tileSize;
    QPair<int, int> floorSize;
    QGraphicsScene *scene;
    QVector<QVector <Tile*>> tiles;
    QVector<Robot*> robots;
};

#endif // FLOOR_H
