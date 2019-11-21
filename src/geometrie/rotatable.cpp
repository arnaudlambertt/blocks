#include "rotatable.h"
#include "../blocs/bloc.h"

Rotatable::Rotatable(const double &rotation)
: m_rotation{rotation}
{
    //ctor
}

Rotatable::~Rotatable()
{
    //dtor
}

Coords Rotatable::convertPosRot(const Coords &basepos, const Coords &localpos) const
{
    double angle = m_rotation * 360.0;
    Coords resultat = localpos;
    Transformation transfo { Rotation{basepos, angle} };
    transfo.appliquer(resultat);

    return resultat;
}

void Rotatable::dessinerAxe(const Bloc* parent, const Geometrie* rot, Svgfile &svgout)
{
    if(parent != nullptr)
        svgout.addCircle(rot->getAbsolute(parent,rot->getBasepos()).getX(),rot->getAbsolute(parent,rot->getBasepos()).getY(),5,2,"red");
}
