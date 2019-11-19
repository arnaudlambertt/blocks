#include "rectangle_translatable.h"

RectangleTranslatable::RectangleTranslatable(const double &width, const double &height,
const std::string &basepos,
const std::string &refpos, const double &refposX, const double &refposY,
const std::string &endpos, const double &translation)
:   Rectangle{width,height,basepos,refpos,refposX,refposY},Translatable{Rectangle::m_refpos,endpos,translation}
{
    m_refpos = calcRefpos();
}

RectangleTranslatable::~RectangleTranslatable()
{
    //dtor
}
