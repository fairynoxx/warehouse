#include "package.h"
#include <QDebug>

/*!
 * \brief Constructor of the class
 * \param pkgId - ID of the package
 * \param pkgType - type of the package
 */
Package::Package(int pkgId, PackageType pkgType)
{
    id = pkgId;
    type = pkgType;
    status = PackageStatus::waiting;
}

/*!
 * \brief Changes stastus of the package
 * \param pkgStatus - status of the package
 */
void Package::changeStatus(PackageStatus pkgStatus)
{
    status = pkgStatus;
}

/*!
 * \brief Gives type of the package
 * \return type of the package
 */
PackageType Package::getPackageType()
{
    return type;
}

/*!
 * \brief Gives the stastus of the package
 * \return status of the package
 */
PackageStatus Package::getPackageStatus()
{
    return status;
}

/*!
 * \brief Gives ID of the package
 * \return ID of the package
 */
int Package::getPackageId()
{
    return id;
}
