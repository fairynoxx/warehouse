#include "floor.h"
#include "ui_floor.h"
#include <QDebug>
#include <algorithm>
#include "shelf.h"


/*!
 * \brief Constructor of the class
 * \param sizeX - height of the warehouse
 * \param sizeY - width of the warehouse
 * \param parent - parent
 */
Floor::Floor(int sizeX, int sizeY, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Floor)
{
    ui->setupUi(this);
    this->floorSize.first = sizeX;
    this->floorSize.second = sizeY;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(ui->graphicsView->rect());
    this->ui->graphicsView->setScene(scene);
    show();
}

/*!
* \brief Destructor of the class
*/
Floor::~Floor()
{
    delete ui;
}

/*!
 * \brief Initializes the floor
 * Determine size of the tiles based on warehouse size, initializes vectors of tiles, sets images for special tiles.
 * \param startTile - position of the start shelf
 * \param endTile - position of the end shelf
 */
void Floor::initFloor(QPair<int,int> startTile, QPair<int,int> endTile)
{
    QSize size = this->ui->graphicsView->size();
    int scale = size.width()/std::max(floorSize.first, floorSize.second);
    this->tileSize = scale;
    for (int i = 0; i < this->floorSize.first; i++)
    {
        QVector<Tile*> column;
        for (int j = 0; j < this->floorSize.second; j++)
        {
            Tile *t = new Tile();
            column.push_back(t);
            column.back()->setX(scale*i);
            column.back()->setY(scale*j);
            column.back()->setScale(double(scale)/500);
            scene->addItem(t);
        }
        this->tiles.push_back(column);
    }
    this->ui->graphicsView->fitInView(ui->graphicsView->rect(),Qt::KeepAspectRatio);
    initializeShelves();
    tiles[startTile.first][startTile.second]->setPixmap(QPixmap(":/images/start_tile.png"));
    tiles[endTile.first][endTile.second]->setPixmap(QPixmap(":/images/start_tile.png"));
}

/*!
 * \brief Sets the size of the warehouse floor
 * \param x - height
 * \param y - width
 */
void Floor::setFloorSize(int x, int y)
{
    this->floorSize.first = y;
    this->floorSize.second = x;
}

/*!
 * \brief Adds robot to the floor
 * \param pos - position of the robot
 */
void Floor::addRobot(QPair<int,int> pos)
{
    Robot *r = new Robot(pos, tileSize);
    robots.push_back(r);
    scene->addItem(r);
}

/*!
 * \brief Adds shelf to the floor
 * \param xPos - x coordinate of the shelf
 * \param yPos - y coordinate of the shelf
 * \param type - type of the shelf
 */
void Floor::addShelf(int xPos, int yPos, PackageType type)
{
    Shelf* s = new Shelf(xPos, yPos, type);
    scene->addItem(s);
    s->setX(xPos*tileSize);
    s->setY(yPos*tileSize);
    s->setScale(double(tileSize)/500);
    shelves[type].push_back(s);
    tiles[xPos][yPos]->changeTileStatus(TileStatus::occupied);
}

/*!
 * \brief Initializes map of the shelves based on possible categories
 */
void Floor::initializeShelves()
{
    QVector<Shelf*> v1;
    shelves.insert(PackageType::cat1, v1);
    QVector<Shelf*> v2;
    shelves.insert(PackageType::cat2, v2);
    QVector<Shelf*> v3;
    shelves.insert(PackageType::cat3, v3);
    QVector<Shelf*> v4;
    shelves.insert(PackageType::cat4, v4);
    QVector<Shelf*> v5;
    shelves.insert(PackageType::start, v4);
}

