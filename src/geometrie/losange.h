#ifndef LOSANGE_H
#define LOSANGE_H

#include "geometrie.h"


class Losange : public Geometrie
{
    public:
        Losange();
        Losange(const double &width, const double &height, const std::string &basepos, const std::string &refpos, const double &refposX, const double &refposY);

        virtual ~Losange();

        static Coords squareposToLosangepos(const Coords &a);

        std::vector<double> getDimensions() const;
        double Getheight() { return m_height; }
        void Setheight(double val) { m_height = val; }
        double Getwidth() { return m_width; }
        void Setwidth(double val) { m_width = val; }

        void dessiner(const std::string &color, const std::string &border, Svgfile &svgout);


        virtual Coords convertRefposEnfant(const Coords &refposEnfant) const;

        using Geometrie::getAbsolute; //qualifier conflict fix
        virtual Coords getAbsolute(const std::string &localPos) const;

    protected:
        double m_height;
        double m_width;

};

#endif // LOSANGE_H
