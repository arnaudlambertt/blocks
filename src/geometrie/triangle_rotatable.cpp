#include "triangle_rotatable.h"

TriangleRotatable::TriangleRotatable(const double &width, const double &height,
                                   const std::string &basepos,
                                   const std::string &refpos, const double &refposX, const double &refposY,
                                   const std::string &endpos, const double &rotation)
    :   Triangle{width,height,basepos,refpos,refposX,refposY},Rotatable{m_refpos,endpos,rotation}
{
    m_refpos = calcRefpos();
}

TriangleRotatable::~TriangleRotatable()
{
    //dtor
}

void TriangleRotatable::dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile& svgout)
{
    dessinerAxe(parent, svgout);
    Triangle::dessiner(parent, color, border, svgout);
}
