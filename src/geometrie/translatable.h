#ifndef TRANSLATABLE_H
#define TRANSLATABLE_H

#include "geometrie.h"

class Translatable
{
    public:
        Translatable(const Coords &startpos, const std::string &endpos, const double &translation);
        virtual ~Translatable();

        void calcRefpos(Coords &refpos);
        void translater(const double &translation, Coords &refpos);

        Coords getEndpos() { return m_endpos; }
        void setEndpos(Coords val) { m_endpos = val; }
        double getTranslation() { return m_translation; }
        void setTranslation(double val) { m_translation = val; }

        void dessinerAxe(const Bloc* parent, Svgfile &svgout);

    protected:
        Coords m_startpos;
        Coords m_endpos;
        double m_translation;
};

#endif // TRANSLATABLE_H
