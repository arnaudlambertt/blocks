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

    Coords getAbsolute(const Bloc* parent, const Coords &localPos) const;

    void dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile &svgout);
};

#endif // DISK_ROTATABLE_H
