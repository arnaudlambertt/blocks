#include "bloc.h"

std::map<char,double> pos = {{'t',-0.5},{'m',0},{'b',0.5},{'l',-0.5},{'c',0},{'r',0.5}};

Bloc::Bloc()
: Bloc{nullptr, "emptyId", 99.0,99.0, {0,0,0}, {0,0,0}, "tl","tl",0.0,0.0}
{
    //ctor
}

Bloc::Bloc(Bloc* parent, std::string id, double width, double height, Couleur color, Couleur border, std::string basepos, std::string refpos, double refposX, double refposY)
: m_parent{parent}, m_id{id}, m_width{width}, m_height{height}, m_color{color}, m_border{border},
  m_basepos{Coords { pos[basepos[1]] , pos[basepos[0]] }},
  m_refpos{Coords { pos[refpos[1]] + refposX, pos[refpos[0]] + refposY }}
{
    //ctor
}

Bloc::~Bloc()
{
    //dtor
}

Coords Bloc::absoluteCoords(Coords localPos) const
{
    Coords absolute;

    if(m_parent != nullptr) //calcul absolute coords de basepos
        {
            absolute.setY( m_parent->absoluteCoords( m_parent->getBasepos() ).getY() + ( m_refpos.getY() - m_parent->getBasepos().getY() )  * m_parent->getHeight() );
            absolute.setX( m_parent->absoluteCoords( m_parent->getBasepos() ).getX() + ( m_refpos.getX() - m_parent->getBasepos().getX() )  * m_parent->getWidth() );
        }

    else
        absolute = {0,0};

    if(m_basepos.getY() != localPos.getY())
        absolute.setY( absolute.getY() + (localPos.getY() - m_basepos.getY())* m_height );

    if(m_basepos.getX() != localPos.getX())
        absolute.setX( absolute.getX() + (localPos.getX() - m_basepos.getX())* m_width );



    return absolute;
}

Coords Bloc::absoluteCoords(std::string localPos) const
{
    return absoluteCoords(Coords{ pos[localPos[1]], pos[localPos[0]]});
}
