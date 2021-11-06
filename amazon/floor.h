#ifndef FLOOR_H
#define FLOOR_H

#include <QWidget>
#include <QPair>
#include <QPainter>

namespace Ui {
class floor;
}

class floor : public QWidget
{
    Q_OBJECT

public:
    explicit floor(int sizeX, int sizeY, QWidget *parent = nullptr);
    ~floor();
    void drawNet();

private:
    Ui::floor *ui;
    QPair<int, int> floorSize;
};

#endif // FLOOR_H
