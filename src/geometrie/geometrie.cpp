#include "../blocs/bloc.h"
#include "geometrie.h"

Geometrie::Geometrie(std::string basepos, std::string refpos, double refposX, double refposY)
{
    m_basepos = {Coords { pos()[basepos[1]] , pos()[basepos[0]] }};
    m_refpos = {Coords { pos()[refpos[1]] + refposX, pos()[refpos[0]] + refposY }};
}

Coords Geometrie::calculerAbsoluteCoords(const Bloc* parent, Coords localPos) const
{
    Coords absolute;

    if(parent != nullptr) //calcul absolute coords de basepos
        {
            if(dynamic_cast<Disk*>(parent->getGeometrie()))
            {
                absolute.setY( parent->calculerAbsoluteCoords( parent->getBasepos() ).getY() + ( squareposToDiskpos(m_refpos).getY() - (parent->getBasepos()).getY() )  * parent->getDimensions()[1] );
                absolute.setX( parent->calculerAbsoluteCoords( parent->getBasepos() ).getX() + ( squareposToDiskpos(m_refpos).getX() - (parent->getBasepos()).getX() )  * parent->getDimensions()[0] );
            }
            else
            {
                absolute.setY( parent->calculerAbsoluteCoords( parent->getBasepos() ).getY() + ( m_refpos.getY() - parent->getBasepos().getY() )  * parent->getDimensions()[1] );
                absolute.setX( parent->calculerAbsoluteCoords( parent->getBasepos() ).getX() + ( m_refpos.getX() - parent->getBasepos().getX() )  * parent->getDimensions()[0] );
            }
        }

    else
        absolute = {0,0};

    if(m_basepos.getY() != localPos.getY())
        absolute.setY( absolute.getY() + (localPos.getY() - m_basepos.getY())* getDimensions()[1] );

    if(m_basepos.getX() != localPos.getX())
        absolute.setX( absolute.getX() + (localPos.getX() - m_basepos.getX())* getDimensions()[0] );

    return absolute;
}


std::map<char,double>pos()
{
    return std::map<char,double> {{'t',-0.5},{'m',0},{'b',0.5},{'l',-0.5},{'c',0},{'r',0.5}};
}
