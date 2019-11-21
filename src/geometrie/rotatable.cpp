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

void Rotatable::dessinerAxe(const Bloc* rot, Svgfile &svgout)
{
    if(rot->getParent() != nullptr)
        svgout.addCircle(rot->getAbsolute(rot->getBasepos()).getX(),rot->getAbsolute(rot->getBasepos()).getY(),5,2,"red");
}
