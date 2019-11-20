#include "geometrie.h"
#include "translatable.h"
#include "../blocs/bloc.h"

Translatable::Translatable(const Coords &refpos, const std::string &endpos, const double &translation)
: m_startpos{refpos}, m_translation{translation}
{
    m_endpos = Coords { Geometrie::pos()[endpos[1]] , Geometrie::pos()[endpos[0]] };
}

Translatable::~Translatable()
{
    //dtor
}

Coords Translatable::calcRefpos() const
{
    return m_startpos + m_translation * (m_endpos - m_startpos);
}

void Translatable::dessinerAxe(const Bloc* parent, Svgfile &svgout)
{
    Geometrie* geo = dynamic_cast<Geometrie*> (this);

    if(geo && parent != nullptr)
        svgout.addArrow(parent->getAbsolute(m_startpos).getX(),parent->getAbsolute(m_startpos).getY(),
                        parent->getAbsolute(m_endpos).getX(),parent->getAbsolute(m_endpos).getY(), "red");
}
