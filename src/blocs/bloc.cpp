#include "bloc.h"

Bloc::Bloc()
: Bloc{nullptr, "emptyId", std::make_unique<Disk>(), "white", "black"}
{
    //ctor
}

Bloc::Bloc(Bloc* parent,const std::string &id, std::unique_ptr<Geometrie> geometrie, const std::string &color, const std::string &border)
: m_parent{parent}, m_id{id}, m_color{color}, m_border{border}, m_geometrie(std::move(geometrie))
{
    //ctor
}

Coords Bloc::convertRefposEnfant(const Coords &refposEnfant) const
{
    return m_geometrie->convertRefposEnfant(refposEnfant);
}

Coords Bloc::calculerAbsoluteCoords(const Coords &localPos) const
{
    return m_geometrie->calculerAbsoluteCoords(m_parent, localPos);
}

Coords Bloc::calculerAbsoluteCoords(const std::string &localPos) const
{
    return m_geometrie->calculerAbsoluteCoords(m_parent, localPos);
}

void Bloc::dessiner(Svgfile &svgout)
{
    m_geometrie->dessiner(m_parent, m_color, m_border, svgout);
}
