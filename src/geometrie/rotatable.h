#ifndef ROTATABLE_H
#define ROTATABLE_H

#include "geometrie.h"
#include "transformation.h"

class Rotatable
{
    public:
        Rotatable();
        virtual ~Rotatable();

        static Coords convertPosRot(const Coords &basepos, const Coords &localpos, const double &rotation);
        Coords convertPosRot(const Coords &basepos, const Coords &localpos) const;

        void dessinerAxe(const Bloc* rot, Svgfile &svgout);

    protected:

};

#endif // ROTATABLE_H
