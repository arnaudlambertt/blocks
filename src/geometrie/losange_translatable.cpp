#include "losange_translatable.h"
#include "../blocs/bloc.h"

LosangeTranslatable::LosangeTranslatable(const double &width, const double &height,
        const std::string &basepos,
        const std::string &refpos, const double &refposX, const double &refposY,
        const std::string &endpos, double &translation)
    :   Losange{width,height,basepos,refpos,refposX,refposY},Translatable{this,m_refpos,endpos,translation}
{
    translater(translation);
}

LosangeTranslatable::~LosangeTranslatable()
{
    //dtor
}
