#ifndef GEOMETRIE_H
#define GEOMETRIE_H

#include "../geometrie/coords.h"
#include "../svg/svgfile.h"
#include "../graphisme/couleur.h"
#include <vector>
#include <map>

class Bloc;
class Geometrie
{
    public:
        Geometrie(std::string basepos, std::string refpos, double refposX, double refposY);
        virtual ~Geometrie() = default;

        virtual void dessiner(const Bloc* parent, Couleur color, Couleur border, Svgfile &svgout) = 0;
        Coords getBasepos() const { return m_basepos; }
        Coords getRefpos() const { return m_refpos; }
        virtual std::vector<double> getDimensions() const = 0;

        virtual Coords calculerAbsoluteCoords(const Bloc* parent, Coords localPos) const = 0;
        virtual Coords calculerAbsoluteCoords(const Bloc* parent, std::string localPos) const = 0;

    protected:
        Coords m_basepos; //point d'attache sur son parent
        Coords m_refpos; //point du parent sur lequel basepos s'attache


};

std::map<char,double> pos();

#endif // GEOMETRIE_H
