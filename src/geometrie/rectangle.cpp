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

Coords Rectangle::getAbsolute(const Bloc* parent, const std::string &localPos) const
{
    return getAbsolute(parent, Coords{ pos()[localPos[1]], pos()[localPos[0]]});
}

void Rectangle::dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile &svgout)
{
    svgout.addRectangle(getAbsolute(parent, "tl").getX(),getAbsolute(parent, "tl").getY(),
                        getAbsolute(parent, "tr").getX(),getAbsolute(parent, "tr").getY(),
                        getAbsolute(parent, "br").getX(),getAbsolute(parent, "br").getY(),
                        getAbsolute(parent, "bl").getX(),getAbsolute(parent, "bl").getY(),
                       color,1,border);
}


