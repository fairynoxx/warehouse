#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QGraphicsPixmapItem>

/*!
 * \brief Status of the field
 */
enum TileStatus
{
    occupied,
    empty
};

/*!
 * \brief The Tile class
 *
 * Represents single tile of the warehouse
 */
class Tile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    /*!
     * \brief status of the tile
     */
    TileStatus status = TileStatus::empty;
public:
    /*!
     * \brief constructor of the class
     */
    explicit Tile(QObject *parent = nullptr, QGraphicsItem *parentPix = nullptr);

    /*!
     * \brief change status of the tile
     */
    void changeTileStatus(TileStatus);

    /*!
     * \brief get status of the tile
     * @return status of the tile
     */
    TileStatus getTileStatus();
signals:

};

#endif // TILE_H
