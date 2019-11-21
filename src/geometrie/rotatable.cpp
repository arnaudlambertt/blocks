#include "rotatable.h"
#include "../blocs/bloc.h"

Rotatable::Rotatable(const Coords &refpos, const std::string &endpos, const double &rotation)
: m_startpos{refpos}, m_rotation{rotation}
{
    m_endpos = Coords { Geometrie::pos()[endpos[1]] , Geometrie::pos()[endpos[0]] };
}

Rotatable::~Rotatable()
{
    //dtor
}

Coords Rotatable::calcRefpos() const
{
    return m_startpos + m_rotation * (m_endpos - m_startpos);
}

void Rotatable::dessinerAxe(const Bloc* parent, Svgfile &svgout)
{
    if(parent != nullptr)
        svgout.addArrow(parent->getAbsolute(m_startpos).getX(),parent->getAbsolute(m_startpos).getY(),
                        parent->getAbsolute(m_endpos).getX(),parent->getAbsolute(m_endpos).getY(), "red");
}
