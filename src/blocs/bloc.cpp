#include "bloc.h"
#include "../geometrie/rectangle_translatable.h"
#include "../geometrie/losange_translatable.h"
#include "../geometrie/disk_translatable.h"
#include "../geometrie/triangle_translatable.h"

#include "../geometrie/rectangle_rotatable.h"
#include "../geometrie/losange_rotatable.h"
#include "../geometrie/disk_rotatable.h"
#include "../geometrie/triangle_rotatable.h"

Bloc::Bloc()
    : Bloc{nullptr, "emptyId", std::make_unique<RectangleTranslatable>(200,100,"tl","mc",0.0,0.0,"br",0.75), "orange", "black"}
{
    //ctor
}

Bloc::Bloc(Bloc* parent,const std::string &id, std::unique_ptr<Geometrie> geometrie, const std::string &color, const std::string &border)
    : m_parent{parent}, m_id{id}, m_color{color}, m_border{border}, m_geometrie(std::move(geometrie))
{
    m_geometrie->setBloc(this);

    //TEMPORAIRE
    if (parent != nullptr)
        parent->ajouterEnfantTEMP(this);
}

Coords Bloc::convertRefposEnfant(const Coords &refposEnfant) const
{
    return m_geometrie->convertRefposEnfant(refposEnfant);
}

Coords Bloc::getAbsolute(const Coords &localPos) const
{
    return m_geometrie->getAbsolute(localPos);
}

Coords Bloc::getAbsolute(const std::string &localPos) const
{
    return m_geometrie->getAbsolute(localPos);
}

void Bloc::dessiner(Svgfile &svgout)
{
    m_geometrie->dessiner(m_color, m_border, svgout);
}

void Bloc::updateRotationEnfantsTEMP()
{
    for(auto &i : m_enfants_TEMP)
    {
        i->getGeometrie()->setRotation(i->getGeometrie()->getRotation() + m_geometrie->getRotation());
        i->updateRotationEnfantsTEMP();
    }
}
