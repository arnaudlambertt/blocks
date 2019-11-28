#include "triangle_translatable.h"
#include "../blocs/bloc.h"

TriangleTranslatable::TriangleTranslatable(const double &width, const double &height,
const std::string &basepos,
const std::string &refpos, const double &refposX, const double &refposY,
const std::string &endpos, double &translation)
:   Triangle{width,height,basepos,refpos,refposX,refposY},Translatable{this,m_refpos,endpos,translation}
{
    translater(translation);
}

TriangleTranslatable::~TriangleTranslatable()
{
    //dtor
}

//void TriangleTranslatable::dessiner(Svgfile& svgout)
//{
//    dessinerAxe(m_bloc->getParent(), svgout);
//    Triangle::dessiner(svgout);
//}
