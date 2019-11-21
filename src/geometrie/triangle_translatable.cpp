#include "triangle_translatable.h"

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

void TriangleTranslatable::dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile& svgout)
{
    dessinerAxe(parent, svgout);
    Triangle::dessiner(parent, color, border, svgout);
}
