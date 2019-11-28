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

//void RectangleRotatable::dessiner(Svgfile& svgout)
//{
//    Rectangle::dessiner(svgout);
//    dessinerAxe(m_bloc, svgout);
//}

