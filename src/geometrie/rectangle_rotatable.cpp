#include "rectangle_rotatable.h"

RectangleRotatable::RectangleRotatable(const double &width, const double &height,
                                       const std::string &basepos,
                                       const std::string &refpos, const double &refposX, const double &refposY,
                                       const double &rotation)
    :   Rectangle{width,height,basepos,refpos,refposX,refposY},Rotatable{rotation}
{
    //ctor
}

RectangleRotatable::~RectangleRotatable()
{
    //dtor
}

Coords RectangleRotatable::getAbsolute(const Bloc* parent, const Coords& localPos) const
{
    return convertPosRot( Geometrie::getAbsolute(parent, m_basepos ), Geometrie::getAbsolute(parent, localPos ) );
}

void RectangleRotatable::dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile& svgout)
{
    Rectangle::dessiner(parent, color, border, svgout);
    dessinerAxe(parent, this, svgout);
}

