#include "tile.h"

Tile::Tile(QObject *parent, QGraphicsItem *parentPix) : QObject(parent), QGraphicsPixmapItem(parentPix)
{
    setPixmap(QPixmap(":/images/tile.png"));
}

void Tile::changeTileStatus(TileStatus s)
{
    status = s;
}
