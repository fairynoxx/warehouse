#include "shelf.h"

Shelf::Shelf(int x, int y, QObject *parent, QGraphicsItem *parentPix) : QObject(parent), QGraphicsPixmapItem(parentPix)
{
    posX = x;
    posY = y;
    setPixmap(QPixmap(":/images/shelf.png"));
}
