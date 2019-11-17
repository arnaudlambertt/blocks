#ifndef BLOC_H
#define BLOC_H
#include <vector>
#include "../geometrie/geometrie.h"
#include "../geometrie/rectangle.h"
#include "../geometrie/disk.h"
#include "../graphisme/couleur.h"
#include "../util/util.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>

class Bloc
{
    public:
        Bloc();
        Bloc(Bloc* parent, const std::string &id, std::unique_ptr<Geometrie> geometrie, const std::string &color, const std::string &border);
        virtual ~Bloc() = default;

        Bloc* getParent() const { return m_parent; }
        void setParent(Bloc* val) { m_parent = val; }
        std::string getId() { return m_id; }

        std::string getColor() { return m_color; }
        std::string getBorder() { return m_border; }

        std::vector<double>  getDimensions() const { return m_geometrie->getDimensions(); }

        Coords getBasepos() const { return m_geometrie->getBasepos(); }
        Coords getRefpos() const { return m_geometrie->getRefpos(); }

        Geometrie* getGeometrie() const { return m_geometrie.get(); }

        virtual void dessiner(Svgfile &svgout);

        Coords convertRefposEnfant(const Coords &refposEnfant) const;
        Coords calculerAbsoluteCoords(const Coords &localPos) const;
        Coords calculerAbsoluteCoords(const std::string &localPos) const;

    protected:
        Bloc* m_parent; //pointeur parent
        std::vector <std::unique_ptr<Bloc>> m_enfants; //vecteur pointeurs enfants

        std::string m_id; //id

        std::string m_color; //couleur remplissage
        std::string m_border; //couleur bordure

        std::unique_ptr<Geometrie> m_geometrie;

};

#endif // BLOC_H
