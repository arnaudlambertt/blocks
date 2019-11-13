#ifndef BLOC_H
#define BLOC_H
#include <vector>
#include "../geometrie/geometrie.h"
#include "../geometrie/rectangle.h"
#include "../graphisme/couleur.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>

class Bloc
{
    public:
        Bloc();
        Bloc(Bloc* parent, std::string id, std::unique_ptr<Geometrie> geometrie, Couleur color, Couleur border);
        virtual ~Bloc() = default;

        Bloc* getParent() const { return m_parent; }
        void setParent(Bloc* val) { m_parent = val; }
        std::vector <Bloc*> getEnfants() { return m_enfants; }
        std::string getId() { return m_id; }

        Couleur getColor() { return m_color; }
        Couleur getBorder() { return m_border; }

        std::vector<double>  getDimensions() const { return m_geometrie->getDimensions(); }

        Coords getBasepos() const { return m_geometrie->getBasepos(); }
        Coords getRefpos() const { return m_geometrie->getRefpos(); }

        virtual void dessiner(Svgfile &svgout);

        Coords calculerAbsoluteCoords(Coords localPos) const;
        Coords calculerAbsoluteCoords(std::string localPos) const;

    protected:
        Bloc* m_parent; //pointeur parent
        std::vector <Bloc*> m_enfants; //vecteur pointeurs enfants

        std::string m_id; //id

        Couleur m_color; //couleur remplissage
        Couleur m_border; //couleur bordure

        std::unique_ptr<Geometrie> m_geometrie;

};

extern std::map<char,double> pos;

#endif // BLOC_H