#include "tile.h"

Tile::Tile(QObject *parent, QGraphicsItem *parentPix) : QObject(parent), QGraphicsPixmapItem(parentPix)
{
   setPixmap(QPixmap(":/images/tile.png"));
}
