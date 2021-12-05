#ifndef PACKAGE_H
#define PACKAGE_H


enum class PackageType
{
    ////// TODO add types of packages
    cat1,
    cat2,
    cat3,
    cat4,
    start
};

enum class PackageStatus
{
    ////// TODO idk if this is reasonable
    waiting,
    delivered,
    onTheWay,
};

class Package
{
public:
    Package(int, PackageType);
    ~Package();
private:
    PackageStatus status;
    PackageType type;
public:
    //// TODO MOVE TO PRIVATE, ADD METHOD
    int id;
    ////
    void changeStatus(PackageStatus);
    PackageType getPackageType();
};

#endif // PACKAGE_H
