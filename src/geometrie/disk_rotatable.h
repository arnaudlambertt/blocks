#ifndef DISK_ROTATABLE_H
#define DISK_ROTATABLE_H

#include "disk.h"
#include "rotatable.h"

class DiskRotatable : public Disk, public Rotatable
{
public:
    DiskRotatable(const double &radius, const std::string &basepos, const std::string &refpos,
                  const double &refposX, const double &refposY,
                  const double &rotation);

    virtual ~DiskRotatable();

    //void dessiner(Svgfile &svgout);
};

#endif // DISK_ROTATABLE_H
