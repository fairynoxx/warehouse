#include "tile.h"

/*!
 * \brief constructor of the class
 * \param parent
 * \param parentPix
 */
Tile::Tile(QObject *parent, QGraphicsItem *parentPix) : QObject(parent), QGraphicsPixmapItem(parentPix)
{
    setPixmap(QPixmap(":/images/tile.png"));
}

/*!
 * \brief change status of the tile
 * \param s - status
 */
void Tile::changeTileStatus(TileStatus s)
{
    status = s;
}

/*!
 * \brief get status of the tile
 * \return status of the tile
 */
TileStatus Tile::getTileStatus()
{
    return status;
}
