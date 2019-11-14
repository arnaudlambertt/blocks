#include "bloc.h"

Bloc::Bloc()
: Bloc{nullptr, "emptyId", std::make_unique<Disk>(), {0,0,0}, {0,0,0}}
{
    //ctor
}

Bloc::Bloc(Bloc* parent, std::string id, std::unique_ptr<Geometrie> geometrie, Couleur color, Couleur border)
: m_parent{parent}, m_id{id}, m_color{color}, m_border{border}, m_geometrie(std::move(geometrie))
{
    //ctor
}

Coords Bloc::calculerAbsoluteCoords(Coords localPos) const
{
    return m_geometrie->calculerAbsoluteCoords(m_parent, localPos);
}

Coords Bloc::calculerAbsoluteCoords(std::string localPos) const
{
    return m_geometrie->calculerAbsoluteCoords(m_parent, localPos);
}

void Bloc::dessiner(Svgfile &svgout)
{
    m_geometrie->dessiner(m_parent, m_color, m_border, svgout);
}
