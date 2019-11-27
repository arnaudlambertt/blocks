#include "translatable.h"
#include "../blocs/bloc.h"

Translatable::Translatable(Geometrie* geometrie,const Coords &refpos, const std::string &endpos, const double &translation)
: m_startpos{refpos}, m_translation{translation}, m_geometrie{geometrie}
{
    m_endpos = Coords { Geometrie::pos()[endpos[1]] , Geometrie::pos()[endpos[0]] };
}

Translatable::~Translatable()
{
    //dtor
}

void Translatable::calcRefpos()
{
    m_geometrie->setRefpos(m_startpos + m_translation * (m_endpos - m_startpos));
}

void Translatable::dessinerAxe(const Bloc* parent, Svgfile &svgout)
{
    if(parent != nullptr)
        svgout.addArrow(parent->getAbsolute(m_startpos).getX(),parent->getAbsolute(m_startpos).getY(),
                        parent->getAbsolute(m_endpos).getX(),parent->getAbsolute(m_endpos).getY(), "red");
}

void Translatable::translater(double translation)
{
    std::cout << translation << std::endl;
    translation = std::max(0.0,std::min(translation,1.0));
    m_translation = translation;
    calcRefpos();
}
