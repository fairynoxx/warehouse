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
private:
    QPair<int,int> startTile;
    QPair<int,int> findShelfForPackage(PackageType);
    int numOfPackages = 0;
    QQueue<Package*> packages;
signals:
    void sendOrder(Order*);
};

#endif // SUPERVISOR_H
