#ifndef DISK_H
#define DISK_H

#include "geometrie.h"
#include "math.h"
#include <cstdlib>

class Disk : public Geometrie
{
    public:
        Disk();
        Disk(double radius, std::string basepos, std::string refpos, double refposX, double refposY);

        virtual ~Disk();

        double Getradius() { return m_radius; }
        void Setradius(double val) { m_radius = val; }
        std::vector<double> getDimensions() const;

        virtual void dessiner(const Bloc* parent, Couleur color, Couleur border, Svgfile &svgout);

        virtual Coords convertRefposEnfant(Coords refposEnfant) const;
        virtual Coords calculerAbsoluteCoords(const Bloc* parent, std::string localPos) const;

    protected:
        double m_radius;

    private:
};

double signe(double a);
double abs(double a);
Coords squareposToDiskpos(const Coords &a);



#endif // DISK_H
