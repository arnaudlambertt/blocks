#include "triangle_rotatable.h"

TriangleRotatable::TriangleRotatable(const double &width, const double &height,
                                   const std::string &basepos,
                                   const std::string &refpos, const double &refposX, const double &refposY,
                                   const double &rotation)
    :   Triangle{width,height,basepos,refpos,refposX,refposY},Rotatable{rotation}
{
    //ctor
}

TriangleRotatable::~TriangleRotatable()
{
    //dtor
}

Coords TriangleRotatable::getAbsolute(const Coords& localPos) const
{
    return convertPosRot( Geometrie::getAbsolute(m_basepos ), Geometrie::getAbsolute(localPos ) );
}

void TriangleRotatable::dessiner(const std::string &color, const std::string &border, Svgfile& svgout)
{
    Triangle::dessiner(color, border, svgout);
    dessinerAxe(m_bloc, svgout);
}
