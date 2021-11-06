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
    void drawNet();

private:
    Ui::Floor *ui;
    QPair<int, int> floorSize;
    QGraphicsScene *scene;
    class Tile *t;
};

#endif // FLOOR_H
