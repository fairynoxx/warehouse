#include "floor.h"
#include "ui_floor.h"


floor::floor(int sizeX, int sizeY, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::floor)
{
    this->floorSize.first = sizeX;
    this->floorSize.second = sizeY;
    ui->setupUi(this);
}

floor::~floor()
{
    delete ui;
}

void floor::drawNet()
{
    QSize size = this->ui->graphicsView->size();

    for (int i = 0; i < this->floorSize.first; i++)
    {
        this->ui->graphicsView->
    }
}
