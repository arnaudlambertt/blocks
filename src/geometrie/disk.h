#ifndef DISK_H
#define DISK_H

#include "geometrie.h"
#include "math.h"
#include <cstdlib>

class Disk : public Geometrie
{
    public:
        Disk();
        Disk(const double &radius, const std::string &basepos, const std::string &refpos, const double &refposX, const double &refposY);

        virtual ~Disk();

        double Getradius() { return m_radius; }
        void Setradius(double val) { m_radius = val; }
        std::vector<double> getDimensions() const;

        virtual void dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile &svgout);

        virtual Coords convertRefposEnfant(const Coords &refposEnfant) const;
        virtual Coords calculerAbsoluteCoords(const Bloc* parent, const std::string &localPos) const;

    protected:
        double m_radius;

    private:
};

double signe(double a);
double abs(double a);
Coords squareposToDiskpos(const Coords &a);



#endif // DISK_H
