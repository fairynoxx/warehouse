#include "package.h"

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
