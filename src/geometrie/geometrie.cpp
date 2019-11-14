#include "../blocs/bloc.h"
#include "geometrie.h"

Geometrie::Geometrie(std::string basepos, std::string refpos, double refposX, double refposY)
{
    m_basepos = {Coords { pos()[basepos[1]] , pos()[basepos[0]] }};
    m_refpos = {Coords { pos()[refpos[1]] + refposX, pos()[refpos[0]] + refposY }};
}

std::map<char,double>pos()
{
    return std::map<char,double> {{'t',-0.5},{'m',0},{'b',0.5},{'l',-0.5},{'c',0},{'r',0.5}};
}
