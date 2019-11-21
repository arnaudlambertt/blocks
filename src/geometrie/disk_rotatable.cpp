#include "disk_rotatable.h"

DiskRotatable::DiskRotatable(const double &radius, const std::string &basepos,
                             const std::string &refpos, const double &refposX, const double &refposY,
                             const std::string &endpos, const double &rotation)
    :   Disk{radius,basepos,refpos,refposX,refposY},Rotatable{m_refpos,endpos,rotation}
{
    m_refpos = calcRefpos();
}

DiskRotatable::~DiskRotatable()
{
    //dtor
}

void DiskRotatable::dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile& svgout)
{
    dessinerAxe(parent, svgout);
    Disk::dessiner(parent, color, border, svgout);
}
