#ifndef SHELF_H
#define SHELF_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Shelf : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Shelf(int, int, QObject *parent = nullptr, QGraphicsItem *parentPix = nullptr);
private:
    int posX;
    int posY;
    int unit;
signals:

};

#endif // SHELF_H
