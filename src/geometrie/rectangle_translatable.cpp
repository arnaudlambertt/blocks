#include "rectangle_translatable.h"
#include "../blocs/bloc.h"


RectangleTranslatable::RectangleTranslatable(const double &width, const double &height,
const std::string &basepos,
const std::string &refpos, const double &refposX, const double &refposY,
const std::string &endpos, const double &translation)
:   Rectangle{width,height,basepos,refpos,refposX,refposY},Translatable{Rectangle::m_refpos,endpos,translation}
{
    translater(translation,m_refpos);
}

RectangleTranslatable::~RectangleTranslatable()
{
    //dtor
}

void RectangleTranslatable::dessiner(const std::string &color, const std::string &border, Svgfile& svgout)
{
    dessinerAxe(m_bloc->getParent(), svgout);
    Rectangle::dessiner(color, border, svgout);
}
