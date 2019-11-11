#ifndef BLOC_H
#define BLOC_H
#include <vector>
#include "../svg/svgfile.h"
#include "../geometrie/coords.h"
#include "../graphisme/couleur.h"
#include <iostream>
#include <map>
#include <string>

class Bloc
{
    public:
        Bloc();
        Bloc(Bloc* parent, std::string id, double width, double height, Couleur color, Couleur border, std::string basepos, std::string refpos, double refposX, double refposY);
        virtual ~Bloc();

        Bloc* getParent() { return m_parent; }
        void setParent(Bloc* val) { m_parent = val; }
        std::vector <Bloc*> getEnfants() { return m_enfants; }
        std::string getId() { return m_id; }
        double getWidth() { return m_width; }
        double getHeight() { return m_height; }
        Couleur getColor() { return m_color; }
        Couleur getBorder() { return m_border; }
        Coords getBasepos() { return m_basepos; }
        Coords getRefpos() { return m_refpos; }

        void dessiner(Svgfile &svgout);

        Coords absoluteCoords(Coords localPos) const;
        Coords absoluteCoords(std::string localPos) const;

    protected:
        Bloc* m_parent; //pointeur parent
        std::vector <Bloc*> m_enfants; //vecteur pointeurs enfants

        std::string m_id; //id

        double m_width; //largeur
        double m_height; //hauteur

        Couleur m_color; //couleur remplissage
        Couleur m_border; //couleur bordure

        Coords m_basepos; //point d'attache sur son parent
        Coords m_refpos; //point du parent sur lequel basepos s'attache
};

extern std::map<char,double> pos;

#endif // BLOC_H
