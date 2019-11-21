#include "losange_rotatable.h"

LosangeRotatable::LosangeRotatable(const double &width, const double &height,
                                   const std::string &basepos,
                                   const std::string &refpos, const double &refposX, const double &refposY,
                                   const std::string &endpos, const double &rotation)
    :   Losange{width,height,basepos,refpos,refposX,refposY},Rotatable{m_refpos,endpos,rotation}
{
    m_refpos = calcRefpos();
}

LosangeRotatable::~LosangeRotatable()
{
    //dtor
}

void LosangeRotatable::dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile& svgout)
{
    dessinerAxe(parent, svgout);
    Losange::dessiner(parent, color, border, svgout);
}
