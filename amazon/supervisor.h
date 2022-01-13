#ifndef SUPERVISOR_H
#define SUPERVISOR_H
#include "floor.h"

class Supervisor : public QObject
{
    Q_OBJECT
public:
    Supervisor();
    /**
     * Adds shelf to the warehouse
     */
    void addShelf(int,int,PackageType);

    /**
     * creates new package
     */
    void addPackage(PackageType);
    Floor* floor;
    /**
     * sets start shelf of the warehouse
     */
    void setStartTile(QPair<int,int>);

    /**
     * sets end shelf of the warehouse
     */
    void setEndTile(QPair<int,int>);

    /**
     * checks if there are new packages waiting and prepares an order
     */
    void checkForOrders();

    /**
     * prepares an order for requested package
     */
    void packageRequested(int);

    /**
     *  gives the IDs of all packages on shelves (excluding start and end)
     */
    QVector<int> updateShelves();
private:
    QPair<int,int> startTile;
    QPair<int,int> endTile;

    /**
     * map of all of the packages and shelves that they are on
     */
    QMap<int,Shelf*> packagesOnShelves;

    /**
     * gives position of the free shelf of particular type and
     * adds package ID and shelf to the packagesOnShelves
     */
    QPair<int,int> findShelfForPackage(int,PackageType);
    int numOfPackages = 0;
    QQueue<Package*> packages;
signals:
    void sendOrder(Order*);
};

#endif // SUPERVISOR_H
