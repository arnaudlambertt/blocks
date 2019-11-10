#include "bloc.h"

std::map<char,double> pos = {{'t',-0.5},{'m',0},{'b',0.5},{'l',-0.5},{'c',0},{'r',0.5}};

Bloc::Bloc()
: Bloc{nullptr,100.0,100.0,"tl","tl"}
{
    //ctor
}

Bloc::Bloc(Bloc* parent, double width, double height, std::string basepos, std::string refpos)
: m_parent{parent},m_width{width},m_height{height},m_basepos{basepos},m_refpos{refpos}
{
    //ctor
}

Bloc::~Bloc()
{
    //dtor
}

Coords Bloc::getBaseCoords() const
{
    Coords baseCoords;

    if(m_parent != nullptr)
        {
            baseCoords.setY( m_parent->getBaseCoords().getY() + ( pos[ this->m_refpos[0] ] - pos[ m_parent->getBasepos()[0] ] ) * m_parent->getHeight() );
            baseCoords.setX( m_parent->getBaseCoords().getX() + ( pos[ this->m_refpos[1] ] - pos[ m_parent->getBasepos()[1] ] ) * m_parent->getWidth() );
        }

    else
        baseCoords = {0,0};

    return baseCoords;
}
