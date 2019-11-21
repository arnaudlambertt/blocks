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

Coords LosangeRotatable::getAbsolute(const Coords& localPos) const
{
    return convertPosRot( Geometrie::getAbsolute(m_basepos ), Geometrie::getAbsolute(localPos ) );
}

void LosangeRotatable::dessiner(const std::string &color, const std::string &border, Svgfile& svgout)
{
    Losange::dessiner(color, border, svgout);
    dessinerAxe(m_bloc, svgout);
}
