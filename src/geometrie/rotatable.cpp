/** \brief classe rotatable
 *
 */

#include "rotatable.h"
#include "../blocs/bloc.h"

Rotatable::Rotatable()
{

}

Rotatable::~Rotatable()
{
    //dtor
}

Coords Rotatable::convertPosRot(const Coords &basepos, const Coords &localpos, const double &rotation)
{
    Coords resultat = localpos;
    Transformation transfo { Rotation{basepos, rotation }};
    transfo.appliquer(resultat);

    return resultat;
}

void Rotatable::dessinerAxe(const Bloc* rot, Svgfile &svgout)
{
    if(rot->getParent() != nullptr)
        svgout.addCircle(rot->getAbsolute(rot->getBasepos()).getX(),rot->getAbsolute(rot->getBasepos()).getY(),5,2,"red");
}
