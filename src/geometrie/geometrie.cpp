#include "../blocs/bloc.h"
#include "geometrie.h"

Geometrie::Geometrie(const std::string &basepos, const std::string &refpos, const double &refposX, const double &refposY)
{
    m_basepos = {Coords { pos()[basepos[1]] , pos()[basepos[0]] }};
    m_refpos = {Coords { std::max(-0.5, std::min(0.5, pos()[refpos[1]] + refposX)), std::max(-0.5, std::min(0.5,pos()[refpos[0]] + refposY)) }};
}

Coords Geometrie::getAbsolute(const Bloc* parent, const Coords &localPos) const
{
    Coords absolute;

    if(parent != nullptr) //calcul absolute coords de basepos
        {
            absolute.setY( parent->getAbsolute( parent->getBasepos() ).getY()
                + ( parent->convertRefposEnfant(m_refpos).getY() - (parent->getBasepos()).getY() )  * parent->getDimensions()[1] );

            absolute.setX( parent->getAbsolute( parent->getBasepos() ).getX()
                + ( parent->convertRefposEnfant(m_refpos).getX() - (parent->getBasepos()).getX() )  * parent->getDimensions()[0] );
        }

    else
        absolute = {0,0};

    if(m_basepos.getY() != localPos.getY())
        absolute.setY( absolute.getY() + (localPos.getY() - m_basepos.getY())* getDimensions()[1] );

    if(m_basepos.getX() != localPos.getX())
        absolute.setX( absolute.getX() + (localPos.getX() - m_basepos.getX())* getDimensions()[0] );

    return absolute;
}

