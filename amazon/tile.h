#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Tile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Tile(QObject *parent = nullptr, QGraphicsItem *parentPix = nullptr);

signals:

};

#endif // TILE_H
