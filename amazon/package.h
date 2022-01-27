#ifndef PACKAGE_H
#define PACKAGE_H
#include <QPair>

/*!
 * \brief Type of the package
 */
enum class PackageType
{
    cat1,
    cat2,
    cat3,
    cat4,
    start,
    end
};

/*!
 * \brief Status of the package
 * waiting - order created for the package
 * delivered - order was completed, package is on its shelf
 * onTheWay - package is on the way
 */
enum class PackageStatus
{
    waiting,
    delivered,
    onTheWay,
};

/*!
 * \brief Order
 * pkgId - id of the package
 * posStart - position of the shelf on which package is waiting
 * posEnd - position of the destination shelf
 */
struct Order
{
    QPair<int,int> posStart;
    QPair<int,int> posEnd;
    int pkgId;
};

/*!
 * \brief The Package class
 * Represents single package in the warehouse
 */
class Package
{
public:
    /*!
     * \brief Constructor of the class
     */
    Package(int, PackageType);

    /*!
     * \brief Changes stastus of the package
     */
    void changeStatus(PackageStatus);

    /*!
     * \brief Gives type of the package
     */
    PackageType getPackageType();

    /*!
     * \brief Gives the stastus of the package
     */
    PackageStatus getPackageStatus();

    /*!
     * \brief Gives ID of the package
     */
    int getPackageId();
private:
    /*!
     * \brief Status of the package
     */
    PackageStatus status;

    /*!
     * \brief Type of the package
     */
    PackageType type;

    /*!
     * \brief ID of the package
     */
    int id;
};

#endif // PACKAGE_H
