#include "floor.h"
#include "ui_floor.h"


Floor::Floor(int sizeX, int sizeY, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Floor)
{
    this->floorSize.first = sizeX;
    this->floorSize.second = sizeY;
    scene = new QGraphicsScene();
   // scene->setSceneRect(ui->graphicsView->rect());
    this->ui->graphicsView->setScene(scene);
    t = new class Tile(this);
    scene->addItem(t);
    ui->setupUi(this);
}

Floor::~Floor()
{
    delete ui;
}

void Floor::drawNet()
{
    QSize size = this->ui->graphicsView->size();

    for (int i = 0; i < this->floorSize.first; i++)
    {
    }
}
