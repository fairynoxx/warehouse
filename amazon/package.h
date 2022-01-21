#ifndef PACKAGE_H
#define PACKAGE_H
#include <QPair>


enum class PackageType
{
    ////// TODO add types of packages
    cat1,
    cat2,
    cat3,
    cat4,
    start,
    end
};

enum class PackageStatus
{
    ////// TODO idk if this is reasonable
    waiting,
    delivered,
    onTheWay,
};

struct Order
{
    QPair<int,int> posStart;
    QPair<int,int> posEnd;
    int pkgId;
};

class Package
{
public:
    Package(int, PackageType);
    ~Package();
private:
    PackageStatus status;
    PackageType type;
    int id;
public:
    //// TODO MOVE TO PRIVATE, ADD METHOD
    ////
    void changeStatus(PackageStatus);
    PackageType getPackageType();
    PackageStatus getPackageStatus();
    int getPackageId();
};

#endif // PACKAGE_H
