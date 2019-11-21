#ifndef ROTATABLE_H
#define ROTATABLE_H

#include "geometrie.h"
#include "transformation.h"

class Rotatable
{
    public:
        Rotatable(const double &Rotation);
        virtual ~Rotatable();

        double getRotation() { return m_rotation; }
        void setRotation(double val) { m_rotation = val; }

        Coords convertPosRot(const Coords &basepos, const Coords &localpos) const;

        void dessinerAxe(const Bloc* rot, Svgfile &svgout);

    protected:

        double m_rotation;
};

#endif // ROTATABLE_H
