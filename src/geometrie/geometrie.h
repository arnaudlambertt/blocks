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
        Geometrie(const std::string &basepos, const std::string &refpos, const double &refposX, const double &refposY);
        virtual ~Geometrie() = default;

        virtual void dessiner(const Bloc* parent, const Couleur &color, const Couleur &border, Svgfile &svgout) = 0;
        Coords getBasepos() const { return m_basepos; }
        Coords getRefpos() const { return m_refpos; }
        virtual std::vector<double> getDimensions() const = 0;


        Coords calculerAbsoluteCoords(const Bloc* parent, const Coords &localPos) const;
        virtual Coords convertRefposEnfant(const Coords &refposEnfant) const = 0;
        virtual Coords calculerAbsoluteCoords(const Bloc* parent, const std::string &localPos) const = 0;

    protected:
        Coords m_basepos; //point d'attache sur son parent
        Coords m_refpos; //point du parent sur lequel basepos s'attache


};

std::map<char,double> pos();

#endif // GEOMETRIE_H
