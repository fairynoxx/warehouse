#ifndef PACKAGE_H
#define PACKAGE_H


enum class PackageType
{
    ////// TODO add types of packages
    cat1,
    cat2,
    cat3,
    cat4
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
private:
    PackageStatus status;
    PackageType type;
public:
    int id;
    void changeStatus(PackageStatus);
};

#endif // PACKAGE_H
