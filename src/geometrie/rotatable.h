#ifndef ROTATABLE_H
#define ROTATABLE_H

#include <string>
#include "geometrie.h"

class Rotatable
{
    public:
        Rotatable(const Coords &startpos, const std::string &endpos, const double &Rotation);
        virtual ~Rotatable();

        Coords calcRefpos() const;
        Coords getEndpos() { return m_endpos; }
        void setEndpos(Coords val) { m_endpos = val; }
        double getRotation() { return m_rotation; }
        void setRotation(double val) { m_rotation = val; }

        void dessinerAxe(const Bloc* parent, Svgfile &svgout);

    protected:
        Coords m_startpos;
        Coords m_endpos;
        double m_rotation;
};

#endif // ROTATABLE_H
