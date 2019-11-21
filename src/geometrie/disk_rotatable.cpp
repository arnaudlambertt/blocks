#include "disk_rotatable.h"


DiskRotatable::DiskRotatable(const double &radius, const std::string &basepos,
                             const std::string &refpos, const double &refposX, const double &refposY,
                             const double &rotation)
    :   Disk{radius,basepos,refpos,refposX,refposY},Rotatable{rotation}
{
    //ctor
}

DiskRotatable::~DiskRotatable()
{
    //dtor
}

Coords DiskRotatable::getAbsolute(const Coords& localPos) const
{
    return convertPosRot( Geometrie::getAbsolute(m_basepos ), Geometrie::getAbsolute(localPos ) );
}

void DiskRotatable::dessiner(const std::string &color, const std::string &border, Svgfile& svgout)
{
    Disk::dessiner(color, border, svgout);
    dessinerAxe(m_bloc, svgout);
}
