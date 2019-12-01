#ifndef BLOC_H
#define BLOC_H

#include "geometrie.h"

#include "../util/util.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <sstream>

struct Save
{
    std::string dimension1 = "50";
    std::string dimension2 = "50";

    std::string refpos = "br";
    std::string refposX = "";
    std::string refposY = "";

    std::string endpos = "br";
    std::string basepos = "";
    std::string translation = "";
};

class Bloc
{
    public:
//        Bloc();
//        Bloc(Bloc* parent, const std::string &id, std::unique_ptr<Geometrie> geometrie,
//             const std::string &color, const std::string &border);
        Bloc(std::istream& ifs, Bloc* parent, bool &child);
        virtual ~Bloc() = default;

        void initMembers(std::map<std::string,std::string> &infos);

        Bloc* getParent() const { return m_parent; }
        void setParent(Bloc* val) { m_parent = val; }

        std::vector<Bloc*> getEnfants();

        std::string getId() { return m_id; }
        std::string getName();
        bool testId(const std::string &id);
        void searchId(std::vector<std::string> id, std::vector<Bloc*> &listCurrent);

        void displayId(Svgfile &svgout);
        void displayRuler(Svgfile &svgout);

        std::string getColor() { return m_color; }
        std::string getBorder() { return m_border; }

        std::vector<double>  getDimensions() const { return m_geometrie->getDimensions(); }

        Coords getBasepos() const { return m_geometrie->getBasepos(); }
        Coords getRefpos() const { return m_geometrie->getRefpos(); }

        Geometrie* getGeometrie() const { return m_geometrie.get(); }

        virtual void dessiner(Svgfile &svgout);
        void dessinerId(Svgfile &svgout);

        Coords convertRefposEnfant(const Coords &refposEnfant) const;
        Coords getAbsolute(const Coords &localPos) const;
        Coords getAbsolute(const std::string &localPos) const;
        void sauvegarde(std::ostream& ofs, int tabulation);

        Bloc * getFirstMovableParent();
        std::list<Bloc*> getTousEnfants();
        bool collision(std::list<Bloc*> tousEnfants);

    private:
        Bloc* m_parent; //pointeur parent
        std::vector <std::unique_ptr<Bloc>> m_enfants; //vecteur pointeurs enfants

        std::string m_id; //id

        std::string m_color; //couleur remplissage
        std::string m_border; //couleur bordure

        std::unique_ptr<Geometrie> m_geometrie;
        bool m_isObject = false;
        Save m_info;


};

#endif // BLOC_H
