#include "rectangle_rotatable.h"


RectangleRotatable::RectangleRotatable(const double &width, const double &height,
                                       const std::string &basepos,
                                       const std::string &refpos, const double &refposX, const double &refposY,
                                       const double &rotation)
    :   Rectangle{width,height,basepos,refpos,refposX,refposY},Rotatable{}
{
    setRotation(rotation);
}

RectangleRotatable::~RectangleRotatable()
{
    //dtor
}

void RectangleRotatable::dessiner(const std::string &color, const std::string &border, Svgfile& svgout)
{
    Rectangle::dessiner(color, border, svgout);
    dessinerAxe(m_bloc, svgout);
}

