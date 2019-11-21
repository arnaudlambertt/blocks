#include "losange_rotatable.h"

LosangeRotatable::LosangeRotatable(const double &width, const double &height,
                                   const std::string &basepos,
                                   const std::string &refpos, const double &refposX, const double &refposY,
                                   const double &rotation)
    :   Losange{width,height,basepos,refpos,refposX,refposY},Rotatable{rotation}
{
    //ctor
}

LosangeRotatable::~LosangeRotatable()
{
    //dtor
}

Coords LosangeRotatable::getAbsolute(const Bloc* parent, const Coords& localPos) const
{
    return convertPosRot( Geometrie::getAbsolute(parent, m_basepos ), Geometrie::getAbsolute(parent, localPos ) );
}

void LosangeRotatable::dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile& svgout)
{
    Losange::dessiner(parent, color, border, svgout);
    dessinerAxe(parent, this, svgout);
}
