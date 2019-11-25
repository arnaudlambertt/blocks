#include "losange_rotatable.h"


LosangeRotatable::LosangeRotatable(const double &width, const double &height,
                                   const std::string &basepos,
                                   const std::string &refpos, const double &refposX, const double &refposY,
                                   const double &rotation)
    :   Losange{width,height,basepos,refpos,refposX,refposY},Rotatable{}
{
    setRotation(rotation);
}

LosangeRotatable::~LosangeRotatable()
{
    //dtor
}

void LosangeRotatable::dessiner(Svgfile& svgout)
{
    Losange::dessiner(svgout);
    dessinerAxe(m_bloc, svgout);
}
