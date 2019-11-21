#include "disk_rotatable.h"

DiskRotatable::DiskRotatable(const double &radius, const std::string &basepos,
                             const std::string &refpos, const double &refposX, const double &refposY,
                             const double &rotation)
    :   Disk{radius,basepos,refpos,refposX,refposY},Rotatable{rotation}
{

}

DiskRotatable::~DiskRotatable()
{
    //dtor
}

Coords DiskRotatable::getAbsolute(const Bloc* parent, const Coords& localPos) const
{
    return convertPosRot( Geometrie::getAbsolute(parent, m_basepos ), Geometrie::getAbsolute(parent, localPos ) );
}

void DiskRotatable::dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile& svgout)
{
    Disk::dessiner(parent, color, border, svgout);
    dessinerAxe(parent, this, svgout);
}
