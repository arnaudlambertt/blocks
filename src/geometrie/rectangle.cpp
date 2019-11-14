#include "rectangle.h"
#include "../blocs/bloc.h"
#include "disk.h"

Rectangle::Rectangle()
: Rectangle{100.0,100.0,"tl","bc",0.0,0.0}
{
    //ctor
}

Rectangle::Rectangle(double width, double height,std::string basepos, std::string refpos, double refposX, double refposY)
:   Geometrie{basepos,refpos,refposX,refposY},m_height{height}, m_width{width}
{
    //ctor
}

Rectangle::~Rectangle()
{
    //dtor
}

Coords Rectangle::convertRefposEnfant(Coords refposEnfant) const
{
    return refposEnfant;
}

Coords Rectangle::calculerAbsoluteCoords(const Bloc* parent, std::string localPos) const
{
    return Geometrie::calculerAbsoluteCoords(parent, Coords{ pos()[localPos[1]], pos()[localPos[0]]});
}

void Rectangle::dessiner(const Bloc* parent, Couleur color, Couleur border, Svgfile &svgout)
{
    svgout.addRectangle(calculerAbsoluteCoords(parent, "tl").getX(),calculerAbsoluteCoords(parent, "tl").getY(),
                        calculerAbsoluteCoords(parent, "br").getX(),calculerAbsoluteCoords(parent, "br").getY(),
                       color,1,border);
}

std::vector<double> Rectangle::getDimensions() const
{
    return std::vector<double> {m_width,m_height};
}
