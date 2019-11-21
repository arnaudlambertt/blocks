#include "triangle_translatable.h"
#include "../blocs/bloc.h"

TriangleTranslatable::TriangleTranslatable(const double &width, const double &height,
const std::string &basepos,
const std::string &refpos, const double &refposX, const double &refposY,
const std::string &endpos, const double &translation)
:   Triangle{width,height,basepos,refpos,refposX,refposY},Translatable{m_refpos,endpos,translation}
{
    translater(translation,m_refpos);
}

TriangleTranslatable::~TriangleTranslatable()
{
    //dtor
}

void TriangleTranslatable::dessiner(const std::string &color, const std::string &border, Svgfile& svgout)
{
    dessinerAxe(m_bloc->getParent(), svgout);
    Triangle::dessiner(color, border, svgout);
}
