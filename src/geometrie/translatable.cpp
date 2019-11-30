#include "translatable.h"
#include "../blocs/bloc.h"

Translatable::Translatable(Geometrie* geometrie,const Coords &refpos, const std::string &endpos, const double &translation)
    : m_startpos{refpos}, m_translation{translation}, m_geometrie{geometrie}
{
    m_endpos = Coords { Geometrie::pos()[endpos[1]], Geometrie::pos()[endpos[0]] };
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
//    if(parent != nullptr)
//    {
//        Coords basey {0,0.1}, basex{0.1,0}, trg{0.1,0.0};
//        svgout.addLine(parent->getAbsolute(m_startpos).getX(),parent->getAbsolute(m_startpos).getY(),
//                       parent->getAbsolute(m_endpos).getX(),parent->getAbsolute(m_endpos).getY(),"red");
//        if(m_startpos.getX()-m_endpos.getX() == 0 )
//        {
//
//            svgout.addRectangle(parent->getAbsolute(m_startpos-basex).getX(),parent->getAbsolute(m_startpos-basex).getY(),
//                                parent->getAbsolute(m_startpos+basex).getX(),parent->getAbsolute(m_startpos+basex).getY(),
//                                parent->getAbsolute(m_startpos+basex).getX(),parent->getAbsolute(m_startpos+basex).getY(),
//                                parent->getAbsolute(m_startpos-basex).getX(),parent->getAbsolute(m_startpos-basex).getY(),"red",2.5,"red");
//            svgout.addTriangle( parent->getAbsolute(m_endpos-basey).getX(),parent->getAbsolute(m_endpos-basey).getY(),
//                                parent->getAbsolute(m_endpos-basex).getX(),parent->getAbsolute(m_endpos+basex).getY(),
//                                parent->getAbsolute(m_endpos+basex).getX(),parent->getAbsolute(m_endpos+basex).getY(),"red");
//
//        }
//        else if(m_startpos.getY()-m_endpos.getY() == 0 )
//        {
//            svgout.addRectangle(parent->getAbsolute(m_startpos-basey).getX(),parent->getAbsolute(m_startpos-basey).getY(),
//                                parent->getAbsolute(m_startpos+basey).getX(),parent->getAbsolute(m_startpos+basey).getY(),
//                                parent->getAbsolute(m_startpos+basey).getX(),parent->getAbsolute(m_startpos+basey).getY(),
//                                parent->getAbsolute(m_startpos-basey).getX(),parent->getAbsolute(m_startpos-basey).getY(),"red",2.5,"red");
//                                std::cout << "cc" << std::endl;
//            svgout.addTriangle( parent->getAbsolute(m_endpos+basex).getX(),parent->getAbsolute(m_endpos+basex).getY(),
//                                parent->getAbsolute(m_endpos-basey).getX(),parent->getAbsolute(m_endpos-basey).getY(),
//                                parent->getAbsolute(m_endpos+basey).getX(),parent->getAbsolute(m_endpos-basey).getY(),"red");
//        }
//
//    }
        if(parent != nullptr)
        svgout.addArrow(parent->getAbsolute(m_startpos).getX(),parent->getAbsolute(m_startpos).getY(),
                        parent->getAbsolute(m_endpos).getX(),parent->getAbsolute(m_endpos).getY(), "red");
}

void Translatable::translater(double translation)
{
    translation = std::max(0.0,std::min(translation,1.0));
    m_translation = translation;
    calcRefpos();
}
