#include "disk_rotatable.h"


DiskRotatable::DiskRotatable(const double &radius, const std::string &basepos,
                             const std::string &refpos, const double &refposX, const double &refposY,
                             const double &rotation)
    :   Disk{radius,basepos,refpos,refposX,refposY},Rotatable{}
{
    setRotation(rotation);
}

DiskRotatable::~DiskRotatable()
{
    //dtor
}
