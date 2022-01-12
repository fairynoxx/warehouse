#ifndef SUPERVISOR_H
#define SUPERVISOR_H
#include "floor.h"

class Supervisor : public QObject
{
    Q_OBJECT
public:
    Supervisor();
    void addShelf(int,int,PackageType);
    void addPackage(PackageType);
    Floor* floor;
    void setStartTile(QPair<int,int>);
    void checkForOrders();
signals:
    void sendOrder(Order*);
private:
    QQueue<Package*> packages;
    int numOfPackages = 0;
    QPair<int,int> startTile;
};

#endif // SUPERVISOR_H
