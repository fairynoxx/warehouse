#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QGraphicsPixmapItem>


enum TileStatus
{
    occupied,
    empty
};

class Tile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Tile(QObject *parent = nullptr, QGraphicsItem *parentPix = nullptr);
    TileStatus status = TileStatus::empty;
    void changeTileStatus(TileStatus);
signals:

};

#endif // TILE_H
