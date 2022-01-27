#ifndef SHELF_H
#define SHELF_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "package.h"

#define MAX_PKGS 10

/*!
 * \brief The Shelf class
 * Represents one shelf on the floor of the warehouse
 */
class Shelf : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor of the class
     */
    explicit Shelf(int, int, PackageType, QObject *parent = nullptr, QGraphicsItem *parentPix = nullptr);
private:
    /*!
     * \brief Scale of one tile size
     */
    int unit;

    /*!
     * \brief Parameter that says if the shelf is full
     */
    bool isFull = false;

    /*!
     * \brief Parameter that says if the shelf is full
     */
    bool isEmpty = true;

    /*!
     * \brief Type of the shelf
     */
    PackageType type;

    /*!
     * \brief Map of the packages (key - ID of the package, value - pointer to a package)
     */
    QMap<int, Package*> packages;

    /*!
     * \brief Sets image of the shelf based on type and fill
     */
    void setImage();
public:
    /*!
     * \brief x coordinate of the shelf position
     */
    int posX;

    /*!
     * \brief y coordinate of the shelf position
     */
    int posY;

    /*!
     * \brief Adds package to the shelf
     */
    void addPackage(Package*);

    /*!
     * \brief Removes package from the shelf
     */
    Package* removePackage(int);

    /*!
     * \brief Says if shelf is full
     */
    bool isShelfFull();

    /*!
     * \brief Says if shelf is empty
     */
    bool isShelfEmpty();

    /*!
     * \brief Gives all packages on shelf
     */
    QVector<Package*> getAllPackages();

    /*!
     * \brief Gives IDs of all packages on shelf
     */
    QVector<int> getAvailablePackages();

    /*!
     * \brief Gives shelf type
     */
    PackageType getShelfType();

    /*!
     * \brief Checks if there is package with ID on shelf
     */
    bool isThereAPackage(int);

    /*!
     * \brief Gives position of the shelf
     */
    QPair<int,int> getShelfPosition();

    /*!
     * \brief Sets status of the package on shelf
     */
    void changePackageStatus(int, PackageStatus);
};

#endif // SHELF_H
