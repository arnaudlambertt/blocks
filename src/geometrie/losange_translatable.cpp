#include "losange_translatable.h"

LosangeTranslatable::LosangeTranslatable(const double &width, const double &height,
const std::string &basepos,
const std::string &refpos, const double &refposX, const double &refposY,
const std::string &endpos, const double &translation)
:   Losange{width,height,basepos,refpos,refposX,refposY},Translatable{m_refpos,endpos,translation}
{
    m_refpos = calcRefpos();
}

LosangeTranslatable::~LosangeTranslatable()
{
    //dtor
}

void LosangeTranslatable::dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile& svgout)
{
    dessinerAxe(parent, svgout);
    Losange::dessiner(parent, color, border, svgout);
}
