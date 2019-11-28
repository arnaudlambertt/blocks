#include "../blocs/bloc.h"
#include "geometrie.h"
#include "rotatable.h"

Geometrie::Geometrie(const std::string &basepos, const std::string &refpos, const double &refposX, const double &refposY)
{
    m_basepos = {Coords { pos()[basepos[1]], pos()[basepos[0]] }};
    m_refpos = {Coords { std::max(-0.5, std::min(0.5, pos()[refpos[1]] + refposX)), std::max(-0.5, std::min(0.5,pos()[refpos[0]] + refposY)) }};
    m_bloc = nullptr;
}

Coords Geometrie::getAbsolute(const Coords &localPos) const
{
    Coords absolute {150,75};
    Coords base;

    if(m_bloc->getParent() != nullptr) //calcul absolute coords de basepos
        absolute = m_bloc->getParent()->getAbsolute( m_bloc->getParent()->convertRefposEnfant(m_refpos));

    base = absolute;

    if(m_basepos.getY() != localPos.getY())
        absolute.setY( absolute.getY() + (localPos.getY() - m_basepos.getY())* getDimensions()[1] );

    if(m_basepos.getX() != localPos.getX())
        absolute.setX( absolute.getX() + (localPos.getX() - m_basepos.getX())* getDimensions()[0] );

    absolute = Rotatable::convertPosRot(base,absolute, m_rotation);

    return absolute;
}

double Geometrie::getVraiRotation() const
{
    if(m_bloc->getParent() != nullptr)
        return getRotation() - m_bloc->getParent()->getGeometrie()->getRotation();
    else
        return getRotation();
}

void Geometrie::setNewRotation(const double &rotation)
{
    double nouv, ancien = m_rotation;
    if(m_bloc->getParent() != nullptr)
        setRotation(nouv = rotation + m_bloc->getParent()->getGeometrie()->getRotation());
    else
        setRotation(nouv = rotation);
    std::cout << m_rotation << " | " << m_bloc->getId() << std::endl;
    for(auto &i : m_bloc->getEnfants())
        i->getGeometrie()->setNewRotation(i->getGeometrie()->getVraiRotation()+nouv-ancien);

}
