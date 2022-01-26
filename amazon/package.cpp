#include "package.h"
#include <QDebug>

Package::Package(int pkgId, PackageType pkgType)
{
    id = pkgId;
    type = pkgType;
    status = PackageStatus::waiting;
}

void Package::changeStatus(PackageStatus pkgStatus)
{
    status = pkgStatus;
}

PackageType Package::getPackageType()
{
    return type;
}

PackageStatus Package::getPackageStatus()
{
    return status;
}

int Package::getPackageId()
{
    return id;
}

Package::~Package()
{
    //qDebug() << "died";
}
