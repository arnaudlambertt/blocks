#include "losange_translatable.h"
#include "../blocs/bloc.h"

LosangeTranslatable::LosangeTranslatable(const double &width, const double &height,
        const std::string &basepos,
        const std::string &refpos, const double &refposX, const double &refposY,
        const std::string &endpos, const double &translation)
    :   Losange{width,height,basepos,refpos,refposX,refposY},Translatable{m_refpos,endpos,translation}
{
    translater(translation,m_refpos);
}

LosangeTranslatable::~LosangeTranslatable()
{
    //dtor
}

void LosangeTranslatable::dessiner(const std::string &color, const std::string &border, Svgfile& svgout)
{
    dessinerAxe(m_bloc->getParent(), svgout);
    Losange::dessiner(color, border, svgout);
}
