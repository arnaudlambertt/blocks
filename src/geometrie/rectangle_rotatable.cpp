#include "rectangle_rotatable.h"

RectangleRotatable::RectangleRotatable(const double &width, const double &height,
                                   const std::string &basepos,
                                   const std::string &refpos, const double &refposX, const double &refposY,
                                   const std::string &endpos, const double &rotation)
    :   Rectangle{width,height,basepos,refpos,refposX,refposY},Rotatable{m_refpos,endpos,rotation}
{
    m_refpos = calcRefpos();
}

RectangleRotatable::~RectangleRotatable()
{
    //dtor
}

void RectangleRotatable::dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile& svgout)
{
    dessinerAxe(parent, svgout);
    Rectangle::dessiner(parent, color, border, svgout);
}
