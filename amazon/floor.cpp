#include "floor.h"
#include "ui_floor.h"
#include <QDebug>
#include <algorithm>
#include "shelf.h"


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
 //   this->ui->graphicsView->fitInView(ui->graphicsView->rect(),Qt::KeepAspectRatio);
}

Floor::~Floor()
{
    delete ui;
}

void Floor::initFloor()
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
            column.back()->setX(scale*j);
            column.back()->setY(scale*i);
            column.back()->setScale(double(scale)/500);
            qDebug()<<t->x() << " " << t->y() << " " << t->scale();

            scene->addItem(t);
        }
        this->tiles.push_back(column);
    }
    this->ui->graphicsView->fitInView(ui->graphicsView->rect(),Qt::KeepAspectRatio);
    initializeShelves();
}

QSize Floor::getsize()
{
    return this->ui->graphicsView->size();
}

void Floor::setFloorSize(int x, int y)
{
    this->floorSize.first = y;
    this->floorSize.second = x;
}

void Floor::addRobot(int x, int y)
{
    Robot *r = new Robot(x, y, tileSize);
    robots.push_back(r);
    scene->addItem(r);
    qDebug() << r->x() << " " << r->y();
}

void Floor::moveRobot(Direction d)
{
    robots[0]->moveRobot(d);
}

void Floor::addShelf(int xPos, int yPos, PackageType type)
{
    Shelf* s = new Shelf(xPos, yPos);
    scene->addItem(s);
    s->setX(xPos*tileSize);
    s->setY(yPos*tileSize);
    s->setScale(double(tileSize)/500);
    shelves[type].push_back(s);
}

void Floor::printShelves()
{
    qDebug() << "cat1";
    for (int i = 0; i < shelves[PackageType::cat1].size(); i++)
        qDebug() << shelves[PackageType::cat1][i]->posX << " " << shelves[PackageType::cat1][i]->posY;
    qDebug() << "cat2";
    for (int i = 0; i < shelves[PackageType::cat2].size(); i++)
        qDebug() << shelves[PackageType::cat2][i]->posX << " " << shelves[PackageType::cat2][i]->posY;
    qDebug() << "cat3";
    for (int i = 0; i < shelves[PackageType::cat3].size(); i++)
        qDebug() << shelves[PackageType::cat3][i]->posX << " " << shelves[PackageType::cat3][i]->posY;
    qDebug() << "cat4";
    for (int i = 0; i < shelves[PackageType::cat4].size(); i++)
        qDebug() << shelves[PackageType::cat4][i]->posX << " " << shelves[PackageType::cat4][i]->posY;

}

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
}
