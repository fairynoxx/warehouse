#ifndef FLOOR_H
#define FLOOR_H

#include <QWidget>
#include <QPair>
#include <QPainter>
#include <QGraphicsScene>
#include "tile.h"
#include "robot.h"
#include "shelf.h"
#include <QQueue>

namespace Ui {
class Floor;
}

/*!
 * \brief The Floor class
 */
class Floor : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor of the class
     */
    explicit Floor(int sizeX, int sizeY, QWidget *parent = nullptr);
    /*!
    * \brief Destructor of the class
    */
    ~Floor();
    /*!
    * \brief Initializes the floor
    */
    void initFloor(QPair<int,int>, QPair<int,int>);

    /*!
     * \brief Sets the size of the warehouse floor
     */
    void setFloorSize(int,int);

    /*!
     * \brief Adds robot to the floor
     */
    void addRobot(QPair<int,int>);

    /*!
     * \brief Adds shelf to the floor
     */
    void addShelf(int, int, PackageType);

    /*!
     * \brief Size of the warehouse
     */
    QPair<int, int> floorSize;

    /*!
     * \brief Vector of vectors of tiles representing n x m warehouse
     */
    QVector<QVector <Tile*>> tiles;

    /*!
     * \brief Map of the vectors of shelves in all categories
     */
    QMap<PackageType, QVector<Shelf*>> shelves;

    /*!
     * \brief Vector of the robots in the warehouse
     */
    QVector<Robot*> robots;
private:
    /*!
     * \brief Graphical interface of the floor
     */
    Ui::Floor *ui;

    /*!
     * \brief size of the single tile based on the warehouse size
     */
    int tileSize;

    /*!
     * \brief Graphics scene of the floor
     */
    QGraphicsScene *scene;

    /*!
     * \brief Initializes map of the shelves
     */
    void initializeShelves();
};


#endif // FLOOR_H
