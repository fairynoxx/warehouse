#ifndef SUPERVISOR_H
#define SUPERVISOR_H
#include "floor.h"

class Supervisor : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor of the class
     */
    Supervisor();
    /*!
     * \brief Adds shelf to the warehouse
     */
    void addShelf(int,int,PackageType);

    /*!
     * \brief Creates new package
     */
    int addPackage(PackageType);
    Floor* floor;
    /*!
     * \brief Start shelf of the warehouse
     */
    void setStartTile(QPair<int,int>);

    /*!
     * \brief Sets end shelf of the warehouse
     */
    void setEndTile(QPair<int,int>);

    /*!
     * \brief Checks if there are new packages waiting and prepares an order
     */
    void checkForOrders();

    /*!
     * \brief Prepares an order for requested package
     */
    void packageRequested(int);

    /*!
     * \brief  Gives vector of all available packages on shelves
     */
    QVector<int> getPackagesOnShelves();
private:

    /*!
     * \brief Position of the start shelf
     */
    QPair<int,int> startTile;

    /*!
     * \brief Position of the end shelf
     */
    QPair<int,int> endTile;

    /*!
     * \brief Map of all of the packages and shelves that they are on
     */
    QMap<int,Shelf*> packagesOnShelves;

    /*!
     * \brief Gives position of the free shelf of particular type and
     * adds package ID and shelf to the packagesOnShelves
     */
    QPair<int,int> findShelfForPackage(int,PackageType);

    /*!
     * \brief  Gives the IDs of all packages on shelves (excluding start and end)
     */
    QVector<int> updateShelves();
    int numOfPackages = 0;
    QQueue<Package*> packages;
    QMap<int,Package*> allPackages;
    QMap<QPair<int,int>,int> stateOfShelves;
public slots:
    void cancelOrder(Order*);
    void orderCompleted(Order*);
signals:
    void sendOrder(Order*);
    void updateLogs(int, PackageType);
};

#endif // SUPERVISOR_H
