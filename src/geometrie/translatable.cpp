#include "geometrie.h"
#include "translatable.h"

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
