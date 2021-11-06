#ifndef FLOOR_H
#define FLOOR_H

#include <QWidget>
#include <QPair>
#include <QPainter>
#include <QGraphicsScene>
#include "tile.h"

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

private:
    Ui::Floor *ui;
    QPair<int, int> floorSize;
    QGraphicsScene *scene;
    QVector<QVector <Tile*>> tiles;
};

#endif // FLOOR_H
