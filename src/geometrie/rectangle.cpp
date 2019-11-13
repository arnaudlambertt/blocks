#include "rectangle.h"
#include "../blocs/bloc.h"

Rectangle::Rectangle()
: Rectangle{100.0,100.0,"tl","bl",0.0,0.0}
{
    //ctor
}

Rectangle::Rectangle(double width, double height, std::string basepos, std::string refpos, double refposX, double refposY)
:   m_height{height}, m_width{width}
{
    m_basepos = {Coords { pos[basepos[1]] , pos[basepos[0]] }};
    m_refpos = {Coords { pos[refpos[1]] + refposX, pos[refpos[0]] + refposY }};
}

Rectangle::~Rectangle()
{
    //dtor
}

Coords Rectangle::calculerAbsoluteCoords(const Bloc* parent, Coords localPos) const
{
    Coords absolute;

    if(parent != nullptr) //calcul absolute coords de basepos
        {
            absolute.setY( parent->calculerAbsoluteCoords( parent->getBasepos() ).getY() + ( m_refpos.getY() - parent->getBasepos().getY() )  * parent->getDimensions()[1] );
            absolute.setX( parent->calculerAbsoluteCoords( parent->getBasepos() ).getX() + ( m_refpos.getX() - parent->getBasepos().getX() )  * parent->getDimensions()[0] );
        }

    else
        absolute = {0,0};

    if(m_basepos.getY() != localPos.getY())
        absolute.setY( absolute.getY() + (localPos.getY() - m_basepos.getY())* m_height );

    if(m_basepos.getX() != localPos.getX())
        absolute.setX( absolute.getX() + (localPos.getX() - m_basepos.getX())* m_width );

    return absolute;
}

Coords Rectangle::calculerAbsoluteCoords(const Bloc* parent, std::string localPos) const
{
    return calculerAbsoluteCoords(parent, Coords{ pos[localPos[1]], pos[localPos[0]]});
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
