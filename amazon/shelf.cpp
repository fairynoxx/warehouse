#include "shelf.h"

/*!
 * \brief Constructor of the class
 * \param x - x coordinate of the position
 * \param y - y coordinate of the position
 * \param t - type of the shelf
 * \param parent - parent
 * \param parentPix - parentPix
 */
Shelf::Shelf(int x, int y, PackageType t, QObject *parent, QGraphicsItem *parentPix) : QObject(parent), QGraphicsPixmapItem(parentPix)
{
    posX = x;
    posY = y;
    type = t;
    setImage();
}

/*!
 * \brief Sets image of the shelf based on type and fill
 */
void Shelf::setImage()
{
    switch (type) {
    case PackageType::cat1:
        if(isShelfFull())
            setPixmap(QPixmap(":/images/shelf_1_full.png"));
        else if(isShelfEmpty())
            setPixmap(QPixmap(":/images/shelf_1_empty.png"));
        else
            setPixmap(QPixmap(":/images/shelf_1.png"));
        break;
    case PackageType::cat2:
        if(isShelfFull())
            setPixmap(QPixmap(":/images/shelf_2_full.png"));
        else if(isShelfEmpty())
            setPixmap(QPixmap(":/images/shelf_2_empty.png"));
        else
            setPixmap(QPixmap(":/images/shelf_2.png"));
        break;
    case PackageType::cat3:
        if(isShelfFull())
            setPixmap(QPixmap(":/images/shelf_3_full.png"));
        else if(isShelfEmpty())
            setPixmap(QPixmap(":/images/shelf_3_empty.png"));
        else
            setPixmap(QPixmap(":/images/shelf_3.png"));
        break;
    case PackageType::cat4:
        if(isShelfFull())
            setPixmap(QPixmap(":/images/shelf_4_full.png"));
        else if(isShelfEmpty())
            setPixmap(QPixmap(":/images/shelf_4_empty.png"));
        else
            setPixmap(QPixmap(":/images/shelf_4.png"));
        break;
    case PackageType::start:
        setPixmap(QPixmap(":/images/start_field.png"));
    default:
        break;
    }
}

/*!
 * \brief Adds package to the shelf
 * \param pkg - pointer to the package
 */
void Shelf::addPackage(Package *pkg)
{
    packages.insert(pkg->getPackageId(), pkg);
    pkg->changeStatus(PackageStatus::delivered);
    if (getShelfType() == PackageType::start || getShelfType() == PackageType::end)
    {
        isFull = false;
    }
    else
    {
        if (packages.size() == MAX_PKGS)
            isFull = true;
        if (isEmpty)
            isEmpty = false;
    }
    setImage();
}

/*!
 * \brief Removes package from the shelf
 * \param id - ID of the package to be removed
 * \return pointer to the removed package
 */
Package* Shelf::removePackage(int id)
{
    Package *pkg = packages.take(id);
    pkg->changeStatus(PackageStatus::onTheWay);
    if (isFull)
        isFull = false;
    if (packages.size() == 0)
        isEmpty = true;
    setImage();
    return pkg;
}

/*!
 * \brief Says if shelf is full
 * \return true if shelf is full, false if shelf is not full
 */
bool Shelf::isShelfFull()
{
    return isFull;
}

/*!
 * \brief Says if shelf is empty
 * \return true if shelf is empty, false if shelf is not empty
 */
bool Shelf::isShelfEmpty()
{
    return isEmpty;
}

/*!
 * \brief Gives all packages on shelf
 * \return vector of all packages on shelf
 */
QVector<Package*> Shelf::getAllPackages()
{
    QVector<Package*> v;
    QList<Package*> l = packages.values();
    for (auto a: l)
        v.push_back(a);
    return v;
}

/*!
 * \brief Gives IDs of all packages on shelf
 * \return vector of all packages IDs
 */
QVector<int> Shelf::getAvailablePackages()
{
    QVector<int> v;
    QList<Package*> l = packages.values();
    for (auto a: l)
        if(a->getPackageStatus() == PackageStatus::delivered)
            v.push_back(a->getPackageId());
    return v;
}

/*!
 * \brief Gives shelf type
 * \return type of the shelf
 */
PackageType Shelf::getShelfType()
{
    return type;
}

/*!
 * \brief Checks if there is package with ID on shelf
 * \param id - ID of the package
 * \return true if there is such package on shelf, false if there is not such package on shelf
 */
bool Shelf::isThereAPackage(int id)
{
    if (packages.keys().contains(id))
        return true;
    return false;
}

/*!
 * \brief Gives position of the shelf
 * \return x, y coordinated of position of the shelf
 */
QPair<int, int> Shelf::getShelfPosition()
{
    return QPair<int,int>(posX,posY);
}

/*!
 * \brief Sets status of the package on shelf
 * \param id - ID of the package which status has to be changed
 * \param status - new status of the package
 */
void Shelf::changePackageStatus(int id, PackageStatus status)
{
    packages[id]->changeStatus(status);
}
