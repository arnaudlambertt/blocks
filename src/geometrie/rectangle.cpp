#include "rectangle.h"
#include "../blocs/bloc.h"
#include "disk.h"

Rectangle::Rectangle()
: Rectangle{100.0,100.0,"tl","br",0.0,0.0}
{
    //ctor
}

Rectangle::Rectangle(const double &width, const double &height,const std::string &basepos, const std::string &refpos, const double &refposX, const double &refposY)
:   Geometrie{basepos,refpos,refposX,refposY},m_height{height}, m_width{width}
{
    //ctor
}

Rectangle::~Rectangle()
{
    //dtor
}

std::vector<double> Rectangle::getDimensions() const
{
    return std::vector<double> {m_width,m_height};
}

Coords Rectangle::convertRefposEnfant(const Coords &refposEnfant) const
{
    return refposEnfant;
}

Coords Rectangle::getAbsolute(const std::string &localPos) const
{
    return getAbsolute(Coords{ pos()[localPos[1]], pos()[localPos[0]]});
}

void Rectangle::dessiner(const std::string &color, const std::string &border, Svgfile &svgout)
{
    svgout.addRectangle(getAbsolute("tl").getX(),getAbsolute("tl").getY(),
                        getAbsolute("tr").getX(),getAbsolute("tr").getY(),
                        getAbsolute("br").getX(),getAbsolute("br").getY(),
                        getAbsolute("bl").getX(),getAbsolute("bl").getY(),
                       color,1,border);
}


