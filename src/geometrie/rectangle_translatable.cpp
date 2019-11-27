#include "rectangle_translatable.h"
#include "../blocs/bloc.h"


RectangleTranslatable::RectangleTranslatable(const double &width, const double &height,
const std::string &basepos,
const std::string &refpos, const double &refposX, const double &refposY,
const std::string &endpos, double &translation)
:   Rectangle{width,height,basepos,refpos,refposX,refposY},Translatable{this,m_refpos,endpos,translation}
{
    translater(translation);
}

RectangleTranslatable::~RectangleTranslatable()
{
    //dtor
}

void RectangleTranslatable::dessiner(Svgfile& svgout)
{
    dessinerAxe(m_bloc->getParent(), svgout);
    Rectangle::dessiner(svgout);
}

