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

Coords TriangleRotatable::getAbsolute(const Bloc* parent, const Coords& localPos) const
{
    return convertPosRot( Geometrie::getAbsolute(parent, m_basepos ), Geometrie::getAbsolute(parent, localPos ) );
}

void TriangleRotatable::dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile& svgout)
{
    Triangle::dessiner(parent, color, border, svgout);
    dessinerAxe(parent, this, svgout);
}
