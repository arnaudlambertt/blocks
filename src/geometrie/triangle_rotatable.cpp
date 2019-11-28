#include "triangle_rotatable.h"

TriangleRotatable::TriangleRotatable(const double &width, const double &height,
                                   const std::string &basepos,
                                   const std::string &refpos, const double &refposX, const double &refposY,
                                   const double &rotation)
    :   Triangle{width,height,basepos,refpos,refposX,refposY},Rotatable{}
{
    setRotation(rotation);
}

TriangleRotatable::~TriangleRotatable()
{
    //dtor
}

//void TriangleRotatable::dessiner(Svgfile& svgout)
//{
//    Triangle::dessiner(svgout);
//    dessinerAxe(m_bloc, svgout);
//}
