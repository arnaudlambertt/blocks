#ifndef BLOC_H
#define BLOC_H
#include <vector>
#include "../svg/svgfile.h"
#include "../geometrie/coords.h"
#include <iostream>
#include <map>
#include <string>

class Bloc
{
    public:
        Bloc();
        Bloc(Bloc* parent, double width, double height, std::string basepos, std::string refpos);
        virtual ~Bloc();

        Bloc* getParent() { return m_parent; }
        void setParent(Bloc* val) { m_parent = val; }
        std::vector <Bloc*> Getenfants() { return m_enfants; }
        void dessiner(Svgfile &svgout);
        Coords getBaseCoords() const;
        double getWidth() const { return m_width; }
        double getHeight() const { return m_height; }
        std::string getBasepos() const{ return m_basepos;}

    protected:
        Bloc* m_parent;
        std::vector <Bloc*> m_enfants;
        double m_width;
        double m_height;
        std::string m_basepos;
        std::string m_refpos;
};

extern std::map<char,double> pos;

#endif // BLOC_H
