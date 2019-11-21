#include "../blocs/bloc.h"
#include "geometrie.h"

Geometrie::Geometrie(const std::string &basepos, const std::string &refpos, const double &refposX, const double &refposY)
{
    m_basepos = {Coords { pos()[basepos[1]] , pos()[basepos[0]] }};
    m_refpos = {Coords { std::max(-0.5, std::min(0.5, pos()[refpos[1]] + refposX)), std::max(-0.5, std::min(0.5,pos()[refpos[0]] + refposY)) }};
    m_bloc = nullptr;
}

Coords Geometrie::getAbsolute(const Coords &localPos) const
{
    Coords absolute {300,300};

    if(m_bloc->getParent() != nullptr) //calcul absolute coords de basepos
        absolute = m_bloc->getParent()->getAbsolute( m_bloc->getParent()->convertRefposEnfant(m_refpos));

    if(m_basepos.getY() != localPos.getY())
        absolute.setY( absolute.getY() + (localPos.getY() - m_basepos.getY())* getDimensions()[1] );

    if(m_basepos.getX() != localPos.getX())
        absolute.setX( absolute.getX() + (localPos.getX() - m_basepos.getX())* getDimensions()[0] );

    return absolute;
}

