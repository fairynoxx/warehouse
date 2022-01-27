#ifndef SUPERVISOR_H
#define SUPERVISOR_H
#include "floor.h"

/*!
 * \brief The Supervisor class
 * Chooses the destination for the packages, sends orders
 */
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
    /*!
     * \brief Pointer to the floor, access to shelves
     */
    Floor* floor;
    /*!
     * \brief Sets start shelf of the warehouse
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
     * \brief Map of all of the packages and shelves that they are on (key - package ID, value - pointer to a shelf)
     */
    QMap<int,Shelf*> packagesOnShelves;

    /*!
     * \brief Gives position of the free shelf of particular type and adds package ID and shelf to the packagesOnShelves
     */
    QPair<int,int> findShelfForPackage(int,PackageType);

    /*!
     * \brief Number of packages
     */
    int numOfPackages = 0;

    /*!
     * \brief Queue of newly arrived packages
     */
    QQueue<Package*> packages;

    /*!
     * \brief Map of all packages (key - ID of the package, value - pointer to the package)
     */
    QMap<int,Package*> allPackages;

    /*!
     * \brief State of the shelves - number of the packages on shelves - updated when the order is created
     */
    QMap<QPair<int,int>,int> stateOfShelves;
public slots:
    /*!
     * \brief Cancels the order when RobotSupervisor gives the signal that there are no free robots
     */
    void cancelOrder(Order*);

    /*!
     * \brief Completes the order
     */
    void orderCompleted(Order*);
signals:
    /*!
     * \brief Sends signal to the Robot Supervisor with new order
     */
    void sendOrder(Order*);

    /*!
     * \brief Updates logs
     */
    void updateLogs(int, PackageType);
};

#endif // SUPERVISOR_H
