#ifndef GEOMETRIE_H
#define GEOMETRIE_H

#include "../geometrie/coords.h"
#include "../svg/svgfile.h"
#include "../graphisme/couleur.h"
#include <iostream>
#include <vector>
#include <map>

class Bloc;
class Geometrie
{
    public:
        Geometrie(const std::string &basepos, const std::string &refpos, const double &refposX, const double &refposY);
        virtual ~Geometrie() = default;

        virtual void dessiner(Svgfile &svgout) = 0;
        Coords getBasepos() const { return m_basepos; }
        Coords getRefpos() const { return m_refpos; }
        void setRefpos(const Coords &val) { m_refpos = val; }
        void setRotation(const double &val) { m_rotation = val; }
        double getRotation() const { return m_rotation; }
        virtual std::vector<double> getDimensions() const = 0;
        Bloc* getBloc() const { return m_bloc; }
        void setBloc(Bloc* bloc) { m_bloc = bloc; }

        virtual Coords convertRefposEnfant(const Coords &refposEnfant) const = 0;
        virtual Coords getAbsolute(const Coords &localPos) const;
        virtual Coords getAbsolute(const std::string &localPos) const = 0;

        static std::map<char,double> pos() { return std::map<char,double> {{'t',-0.5},{'m',0.0},{'b',0.5},{'l',-0.5},{'c',0.0},{'r',0.5}}; }

    protected:
        Coords m_basepos; //point d'attache sur son parent
        Coords m_refpos; //point du parent sur lequel basepos s'attache
        Bloc* m_bloc; // Bloc auquel la forme appartient
        double m_rotation = 0.0 ; //defaut


};



#endif // GEOMETRIE_H
